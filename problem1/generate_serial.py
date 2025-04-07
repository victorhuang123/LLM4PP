# use this file to generate the optimized code from api
# models: gpt-4o-mini, gpt-4o, deepseek-chat(deepseek-v3), deepseek-reasoner(deeseek-r1)

import numpy as np
import os
import argparse
import re
import json
import time

from client.models import LLM4PP_Problem, LLM4PP_Submission
from client.pareval_client import ParEvalDriver
from fastcoder.chatapi import MessageHistory, ChatAPI, get_api_key
from tenacity import retry, stop_after_attempt, wait_exponential
from sentence_transformers import SentenceTransformer
import torch

# import torch_npu
import tqdm
import faiss
import random
import subprocess
import tempfile
from typing import Tuple

from transformers import AutoTokenizer, AutoModelForMaskedLM

base_prompt = """You are a coding expert that rewriting code. You write C and C++ code. The user will give you code and you will provide a different version of the user's code. You need to make sure that the changed code has the same functionality and parameters and return values as the original code.

        # Prompt format

        The user will provide you a JSON dictionary in the following format:

        ```json
        {
            "source_code" : <Initial code>
        }
        ```

        **IMPORTANT:**
        -You need to give the code in this format at the end of your response:
        ```cpp
        <your optimized code here>
        ```
"""


def str2bool(value):
    if value.lower() in ["true", "1", "t", "y", "yes"]:
        return True
    elif value.lower() in ["false", "0", "f", "n", "no"]:
        return False
    else:
        raise ValueError(f"Invalid boolean value: {value}")


@retry(stop=stop_after_attempt(10), wait=wait_exponential(multiplier=1, min=4, max=10))
def get_response_with_retry(chatAPI, model, messages, json_format=False):
    # return chatAPI.get_response(model, messages, json_format)
    try:
        # print(model)
        # print(messages.get_messages())
        response = chatAPI.get_response(model, messages, json_format=json_format)
        # response_dict = json.loads(response)
        # print(response)
        return response

    except Exception as e:
        import traceback

        traceback.print_exc()
        print("请求失败")
        print(e)
        time.sleep(3)
        # logger.error(f"请求失败: {e}")
        raise


def canonicalize_newlines(code: str) -> str:
    """
    Canonicalize multiple newlines to a single newline
    """

    # call clang-format to canonicalize newlines

    return re.sub(r"\n+", "\n", code)


def load_jsonl_data(jsonl_file):
    data = []
    with open(jsonl_file, "r") as f:
        for line in f:
            data.append(json.loads(line))
    return data


def main():
    parser = argparse.ArgumentParser(description="Generate codes with ParEvalDriver.")
    parser.add_argument(
        "--limit",
        type=int,
        default=None,
        help="Limit the number of problems to process (default: no limit).",
    )
    parser.add_argument(
        "--models", nargs="+", required=True, help="List of model paths to evaluate."
    )
    parser.add_argument(
        "--run-index",
        type=int,
        default=1,
        help="Which run number this evaluation is (useful for repeated runs).",
    )
    parser.add_argument(
        "--machine-index",
        type=int,
        default=0,
        help="Index of the machine, e.g., 0..3, to avoid filename collisions.",
    )
    parser.add_argument(
        "--output-dir",
        type=str,
        default="./logs",
        help="Directory where output JSON logs will be saved.",
    )
    parser.add_argument(
        "--generate-times",
        type=int,
        default=1,
    )
    args = parser.parse_args()
    # Load model directly
    generate_times = args.generate_times

    prefix = ""
    # Iterate over the list of provided models
    for model_path in args.models:
        print(f"\nRunning evaluation for model: {model_path}")
        # get api key
        api_key = get_api_key()
        if "deepseek" in model_path:
            # use deepseek api
            chatAPI = ChatAPI(api_key=api_key, base_url="https://api.deepseek.com")
        else:
            # use openai api
            chatAPI = ChatAPI(api_key=api_key, base_url="https://api.openai.com/v1")

        for generate_idx in range(generate_times):
            print(f"Generate {generate_idx} times")
            driver = ParEvalDriver("ParEval/prompts/code_opt_48.json")
            problem_optimized_code = {}
            count = 0
            for problem in driver:
                # Enforce problem count limit
                if args.limit is not None and count >= args.limit:
                    break
                count = count + 1

                print("base")
                prefix = "base_"
                optimizer_prompt = base_prompt
                messages = MessageHistory()
                messages.add_message("system", optimizer_prompt)
                messages.add_message(
                    "user", json.dumps({"solution.cpp": problem.source_code})
                )

                optimized_code = get_response_with_retry(
                    chatAPI, model_path, messages, json_format=False
                )
                # optimized_code = re.sub(r"```cpp|```", "", optimized_code).strip()
                print(optimized_code)

                optimized_code = re.findall(r"```cpp([\s\S]*?)```", optimized_code)[
                    -1
                ].strip()

                problem_id = problem.problem_id
                # save the optimized code
                problem_optimized_code[problem_id] = optimized_code

            # Save responses for this model
            model_suffix = model_path.split("/")[-1]
            if not model_suffix:
                model_suffix = model_path.split("/")[-2]

            output_filename = (
                f"{model_suffix}_machine{args.machine_index}_run{generate_idx}.json"
            )
            output_filename = prefix + output_filename

            # create output directory if not exists
            output_dir = args.output_dir
            output_folder = os.path.join(output_dir, model_path)
            os.makedirs(output_folder, exist_ok=True)
            output_path = os.path.join(output_folder, output_filename)
            print(problem_optimized_code)
            with open(output_path, "w") as f:
                json.dump(problem_optimized_code, f, indent=4)


if __name__ == "__main__":
    main()
