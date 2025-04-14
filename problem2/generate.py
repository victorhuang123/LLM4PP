# use this file to generate the optimized code from api
# models: gpt-4o-mini, gpt-4o, deepseek-chat(deepseek-v3), deepseek-reasoner(deeseek-r1)

from prompt import base_prompt, make_prompt_parallel, make_prompt_serial, serial_prompt, parallel_prompt
import numpy as np
import os
import argparse
import re
import json
import time

from client.models import LLM4PP_Problem, LLM4PP_Submission
from client.pareval_client import ParEvalDriver
from client.pareval_client import ParEvalDriver
from fastcoder.chatapi import MessageHistory, ChatAPI, get_api_key
from tenacity import retry, stop_after_attempt, wait_exponential
from sentence_transformers import SentenceTransformer
import numpy as np
import torch
# import torch_npu
import tqdm
import faiss
import random
import subprocess
import tempfile
from typing import Tuple

from transformers import AutoTokenizer, AutoModelForMaskedLM
    
def str2bool(value):
    if value.lower() in ['true', '1', 't', 'y', 'yes']:
        return True
    elif value.lower() in ['false', '0', 'f', 'n', 'no']:
        return False
    else:
        raise ValueError(f"Invalid boolean value: {value}")
 

# Function to extract function names from C++ code
def grep_function_name(cpp_code):
    cleaned_code = re.sub(r'#.*\n', '', cpp_code)  # Remove preprocessor directives
    cleaned_code = re.sub(r'/\*.*?\*/', '', cleaned_code, flags=re.DOTALL)  # Remove block comments
    cleaned_code = re.sub(r'//.*\n', '\n', cleaned_code)  # Remove line comments
    function_pattern = re.compile(r'(?:inline\s+)?\w+\s+(\w+)\s*\([^)]*\)\s*\{')
    return function_pattern.findall(cleaned_code)

# Compile and check if the optimized code matches the original functions
def compile_and_check(optimized_code: str, source_code: str) -> Tuple[bool, str, bool, str]:
    try:
        with tempfile.NamedTemporaryFile(suffix=".cpp", delete=False, mode="w") as tmp_file:
            tmp_file.write(optimized_code)
            optimized_code_tmp_file_path = tmp_file.name

        # Compile optimized code
        compile_command0 = [
            "g++", optimized_code_tmp_file_path, "-std=c++20", "-O3", "-fopenmp", "-c", "-o", optimized_code_tmp_file_path + ".o"
        ]
        result0 = subprocess.run(compile_command0, capture_output=True, text=True)

        if result0.returncode != 0:
            os.remove(optimized_code_tmp_file_path)
            error_lines = [line for line in result0.stderr.splitlines() if "error:" in line]
            error_message = "\n".join(error_lines)
            return False, f"Compilation failed:\n{error_message}", False, "Compilation failed."

        # Check functions in optimized code
        nm_command0 = ["nm", "-C", optimized_code_tmp_file_path + ".o"]
        nm_result0 = subprocess.run(nm_command0, capture_output=True, text=True)
        nm_stdout0 = nm_result0.stdout
        all_function_name0 = grep_function_name(optimized_code)
        matched_lines0 = [line for line in nm_stdout0.strip().split('\n') if any(char in line for char in all_function_name0)]

        # Compile source code
        with tempfile.NamedTemporaryFile(suffix=".cpp", delete=False, mode="w") as tmp_file:
            tmp_file.write(source_code)
            source_code_tmp_file_path = tmp_file.name

        compile_command1 = [
            "g++", source_code_tmp_file_path, "-std=c++20", "-O3", "-fopenmp", "-c", "-o", source_code_tmp_file_path + ".o"
        ]
        result1 = subprocess.run(compile_command1, capture_output=True, text=True)
        if result1.returncode != 0:
            os.remove(source_code_tmp_file_path)
            error_lines = [line for line in result1.stderr.splitlines() if "error:" in line]
            error_message = "\n".join(error_lines)
            return False, f"Source code compilation failed:\n{error_message}", False, "Compilation failed."

        # Check functions in source code
        nm_command1 = ["nm", "-C", source_code_tmp_file_path + ".o"]
        nm_result1 = subprocess.run(nm_command1, capture_output=True, text=True)
        nm_stdout1 = nm_result1.stdout
        all_function_name1 = grep_function_name(source_code)
        matched_lines1 = [line for line in nm_stdout1.strip().split('\n') if any(char in line for char in all_function_name1)]

        # Extract function parameters
        extract_matched_lines0 = [re.sub(r'^\w+\(|\)$', '', re.search(r'\b(\w+\([^()]*(?:\([^()]*\)[^()]*)*\))', line).group(1)) for line in matched_lines0]
        extract_matched_lines1 = [re.sub(r'^\w+\(|\)$', '', re.search(r'\b(\w+\([^()]*(?:\([^()]*\)[^()]*)*\))', line).group(1)) for line in matched_lines1]

        # Clean up temporary files
        os.remove(optimized_code_tmp_file_path)
        os.remove(source_code_tmp_file_path)

        # Check if function parameters match
        matched = bool(set(extract_matched_lines0) & set(extract_matched_lines1))
        if matched:
            return True, "Compilation succeeded!", True, "Function matched!"
        else:
            return True, "Compilation succeeded!", False, f"Function mismatch! Source code has parameters {extract_matched_lines0}, while optimized code has parameters {extract_matched_lines1}"

    except Exception as e:
        print(e)
        return False, f"An error occurred: {str(e)}", False, ""

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

def encode_in_batches(texts, model, batch_size=256):
    """
    Encode texts in batches using the given model.
    """
    embeddings = []
    for start_idx in (range(0, len(texts), batch_size)):
        batch_texts = texts[start_idx:start_idx+batch_size]

        # Compute embeddings for the current batch and extend the list of embeddings
        embeddings.extend(model.encode(batch_texts, show_progress_bar=False))
    return embeddings

# 在speedup最高的Top10%中随机抽取一个sample
def generate_rag_prompt(problem, 
                        query_embedding, # 待查询问题embedding
                        faiss_index, # 知识库的embedding集合
                        target_to_problem_id, # code对应的problem id
                        training_data_target, 
                        allow_self_match,
                        fast_src_to_tgt, # problem_id 对应的最高的前10%中随机的record
                        is_parallel=False):
    num_top_matches = 10
    while True:
        distances, indices = faiss_index.search(
            np.array([query_embedding]), 
            num_top_matches
        )
        # Filter out same-problem matches if not allowed
        filtered_problems = []
        for idx in indices[0]:
            # print(training_data_target[idx])
            candidate_problem_id = target_to_problem_id[training_data_target[idx]]

            # Only keep if different problem OR self-match is allowed
            if allow_self_match or (candidate_problem_id != problem.problem_id):
                if candidate_problem_id not in filtered_problems:
                    filtered_problems.append(candidate_problem_id)

        # Check if we have at least 2 valid matches
        if len(filtered_problems) >= 2:
            break
        else:
            num_top_matches *= 5
    top2_problems = filtered_problems[:2]
    closest_pair_fastest = []
    for problem_id in top2_problems:
        
        src_problem = fast_src_to_tgt.get(problem_id)
        if src_problem:
            src_code = src_problem.get('src_code', '')
            tgt_code = src_problem.get('target_code', '')
        else:
            src_code = ""
            tgt_code = ""

        # Use canonicalize_newlines if needed
        closest_pair_fastest.append(canonicalize_newlines(src_code))
        closest_pair_fastest.append(canonicalize_newlines(tgt_code))
    if is_parallel:    
        optimizer_prompt = make_prompt_parallel(
                        closest_pair_fastest[0],
                        closest_pair_fastest[1],
                        closest_pair_fastest[2],
                        closest_pair_fastest[3],
                    )
    else: 
        optimizer_prompt = make_prompt_serial(
                    closest_pair_fastest[0],
                    closest_pair_fastest[1],
                    closest_pair_fastest[2],
                    closest_pair_fastest[3],
                )
    return optimizer_prompt


def main():
    parser = argparse.ArgumentParser(description="Generate codes with ParEvalDriver.")
    parser.add_argument(
        "--limit",
        type=int,
        default=None,
        help="Limit the number of problems to process (default: no limit)."
    )
    parser.add_argument(
        "--models",
        nargs="+",
        required=True,
        help="List of model paths to evaluate."
    )
    parser.add_argument(
        "--run-index",
        type=int,
        default=1,
        help="Which run number this evaluation is (useful for repeated runs)."
    )
    parser.add_argument(
        "--machine-index",
        type=int,
        default=0,
        help="Index of the machine, e.g., 0..3, to avoid filename collisions."
    )
    parser.add_argument(
        "--output-dir",
        type=str,
        default="./logs",
        help="Directory where output JSON logs will be saved."
    )
    parser.add_argument(
        "--tp",
        type=int,
        default=1,
    )
    parser.add_argument(
        "--two-stage",
        type=str2bool,
        default=False,
    )
    parser.add_argument(
        "--serial-rag",
        type=str2bool,
        default=False,
    )
    parser.add_argument(
        "--parallel-rag",
        type=str2bool,
        default=False,
    )
    parser.add_argument(
        "--check",
        type=str2bool,
        default=False,
    )
    parser.add_argument(
        "--check-max-retry",
        type=int,
        default=5,
    )
    parser.add_argument(
        "--generate-times",
        type=int,
        default=5,
    )
    args = parser.parse_args()
    model = SentenceTransformer("neulab/codebert-cpp")
    # Load model directly
    generate_times = args.generate_times
    # model.to('npu')
    print("serial_rag:", args.serial_rag)
    print("parallel_rag:", args.parallel_rag)
    # 并行知识库：LLM生成代码
    json_path = "./json_file/parallel.jsonl"
    training_data = load_jsonl_data(json_path)
    
    p_target_to_problem_id = {x["target_code"]: x["problem_id"] for x in training_data}
    if not os.path.exists('p_target_embeddings.npy'):
        p_training_data_target = list(set([x["target_code"] for x in training_data if len(x["target_code"]) <= 2000]))
        target_embeddings = encode_in_batches(p_training_data_target, model, batch_size=128)
        np.save('p_target_embeddings.npy', target_embeddings)
        np.save('p_training_data_target.npy', np.array(p_training_data_target))
        
    p_training_data_target = np.load('p_training_data_target.npy', allow_pickle=True)
    target_embeddings = np.load('p_target_embeddings.npy', allow_pickle=True)
    

    dimension = target_embeddings.shape[1]  # Get the size of the embedding
    p_faiss_index = faiss.IndexFlatL2(dimension)
    p_faiss_index.add(np.array(target_embeddings).astype('float32'))
    
    p_fast_src_to_tgt = {}
            
    # 在speedup最高的Top10%中随机抽取一个sample
    problem_records = {}
    for record in training_data:
        problem_id = record['problem_id']
        if problem_id not in problem_records:
            problem_records[problem_id] = []
        problem_records[problem_id].append(record)
    for problem_id, records in problem_records.items():
        # 按照 speedup 进行降序排序
        filtered_records = [x for x in records if len(x['target_code']) <= 2000]

        if not filtered_records:
            # 如果没有符合条件的记录，可以选择跳过或赋予一个默认值
            continue
        sorted_records = sorted(filtered_records, key=lambda x: x['speedup'], reverse=True)
        # 选择最高的前10%
        top_10_percent_count = max(1, int(len(sorted_records) * 0.1)) # Top 10% 中抽取
        top_10_percent_records = sorted_records[:top_10_percent_count]
        # 从最高的前10%中随机抽取一个 record
        selected_record = random.choice(top_10_percent_records)
        p_fast_src_to_tgt[problem_id] = selected_record
        
    # 串行知识库 pie   
    json_path = json_path = "./json_file/serial.jsonl"
    training_data = load_jsonl_data(json_path)    
    s_target_to_problem_id = {x["target_code"]: x["problem_id"] for x in training_data}
    # s_training_data_target = list(set([x["target_code"] for x in training_data if len(x["target_code"]) <= 2000]))
    # print(len(s_training_data_target))
    # np.save('s_training_data_target.npy', np.array(s_training_data_target))
    # exit(0)
    if not os.path.exists('s_target_embeddings.npy'):
        s_training_data_target = list(set([x["target_code"] for x in training_data for x in training_data if len(x["target_code"]) <= 2000]))
        print(len(s_training_data_target))
        target_embeddings = encode_in_batches(s_training_data_target, model, batch_size=128)
        np.save('s_target_embeddings.npy', target_embeddings)
        np.save('s_training_data_target.npy', np.array(s_training_data_target))
        
    s_training_data_target = np.load('s_training_data_target.npy', allow_pickle=True)
    target_embeddings = np.load('s_target_embeddings.npy', allow_pickle=True)
    
    dimension = target_embeddings.shape[1]  # Get the size of the embedding
    s_faiss_index = faiss.IndexFlatL2(dimension)
    s_faiss_index.add(np.array(target_embeddings).astype('float32'))

    s_fast_src_to_tgt = {}
            
    # 在speedup最高的Top10%中随机抽取一个sample
    problem_records = {}
    for record in training_data:
        problem_id = record['problem_id']
        if problem_id not in problem_records:
            problem_records[problem_id] = []
        problem_records[problem_id].append(record)
    for problem_id, records in problem_records.items():
        # 按照 speedup 进行降序排序
        filtered_records = [x for x in records]

        if not filtered_records:
            # 如果没有符合条件的记录，可以选择跳过或赋予一个默认值
            continue
        sorted_records = sorted(filtered_records, key=lambda x: x['speedup'], reverse=True)
        # 选择最高的前10%
        top_10_percent_count = max(1, int(len(sorted_records) * 0.1)) # Top 10% 中抽取
        top_10_percent_records = sorted_records[:top_10_percent_count]
        # 从最高的前10%中随机抽取一个 record
        selected_record = random.choice(top_10_percent_records)
        s_fast_src_to_tgt[problem_id] = selected_record
    
    prefix = ""   
    # Iterate over the list of provided models
    for model_path in args.models:
        print(f"\nRunning evaluation for model: {model_path}")
        # get api key
        api_key = get_api_key()
        if 'deepseek' in model_path:
            # use deepseek api
            chatAPI = ChatAPI(api_key=api_key, base_url='https://api.deepseek.com')
        elif 'local' in model_path:
            chatAPI = ChatAPI(api_key=api_key, base_url=os.getenv("OPENAI_API_BASE", "http://localhost:8001/v1"))
        else:
            # use openai api
            chatAPI = ChatAPI(api_key=api_key, base_url='https://api.openai.com/v1')

        for generate_idx in range(generate_times):
            print(f"Generate {generate_idx} times")
            driver = ParEvalDriver()
            problem_optimized_code = {}
            count = 0
            for problem in driver:
                # Enforce problem count limit
                if args.limit is not None and count >= args.limit:
                    break
                count = count + 1
                query_code = problem.source_code
                query_embedding = model.encode(query_code).astype('float32')
                
                if not args.two_stage:
                    if (not args.serial_rag) and (not args.parallel_rag):
                        print("base")
                        prefix = "base_"
                        optimizer_prompt = base_prompt
                        messages = MessageHistory()
                        messages.add_message("system", optimizer_prompt)
                        messages.add_message("user", json.dumps({"solution.cpp": problem.source_code}))
                
                        optimized_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                        match = re.search(r'```cpp\s*(.*?)\s*```', optimized_code, re.DOTALL)
                        optimized_code = match.group(1).strip() if match else "No code found."
                        #optimized_code = re.sub(r'```cpp|```', '', optimized_code).strip()
                        if args.check:
                            # check compile
                            print("do check")
                            prefix = prefix + "check_"
                            compile_max_retry = args.check_max_retry
                            for _ in range (compile_max_retry):
                                compile_success, compile_message, function_success, function_message = compile_and_check(optimized_code, query_code)
                                if not compile_success or not function_success:
                                    if not compile_success:
                                        error_message = compile_message
                                    else:
                                        error_message = function_message
                                    prompt_for_correction = f"Here is an message of the optimized code:\nError: {error_message}\nPlease fix the code and regenerate the code."
                                    
                                    # Send error to LLM for correction
                                    messages.add_message("assistant", optimized_code)
                                    messages.add_message("user", prompt_for_correction)
                                    
                                    # Get the corrected code from LLM
                                    corrected_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                                    match = re.search(r'```cpp\s*(.*?)\s*```', corrected_code, re.DOTALL)
                                    optimized_code = match.group(1).strip() if match else "No code found."
                                    #optimized_code = re.sub(r'```cpp|```', '', corrected_code).strip()
                                else:
                                    break
                    else:
                        print("Error in two_stage False")
                        return
                else:
                    if (not args.serial_rag) and (not args.parallel_rag):
                        print("serial then parallel")
                        prefix = "serial_parallel_norag_"
                        messages = MessageHistory()
                        messages.add_message("system", serial_prompt)
                        messages.add_message("user", json.dumps({"solution.cpp": problem.source_code}))
                        optimized_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                        match = re.search(r'```cpp\s*(.*?)\s*```', optimized_code, re.DOTALL)
                        optimized_code = match.group(1).strip() if match else "No code found."
                        #optimized_code = re.sub(r'```cpp|```', '', optimized_code).strip()
                        
                        if args.check:
                            # check compile
                            print("do check")
                            # prefix = prefix + "check_"
                            compile_max_retry = args.check_max_retry
                            for _ in range (compile_max_retry):
                                compile_success, compile_message, function_success, function_message = compile_and_check(optimized_code, query_code)
                                if not compile_success or not function_success:
                                    if not compile_success:
                                        error_message = compile_message
                                    else:
                                        error_message = function_message
                                    prompt_for_correction = f"Here is an message of the optimized code:\nError: {error_message}\nPlease fix the code and regenerate the code."
                                    
                                    # Send error to LLM for correction
                                    messages.add_message("assistant", optimized_code)
                                    messages.add_message("user", prompt_for_correction)
                                    
                                    # Get the corrected code from LLM
                                    corrected_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                                    match = re.search(r'```cpp\s*(.*?)\s*```', corrected_code, re.DOTALL)
                                    optimized_code = match.group(1).strip() if match else "No code found."
                                    #optimized_code = re.sub(r'```cpp|```', '', corrected_code).strip()
                                else:
                                    break
                        #TODO: Check whether context is required
                        messages = MessageHistory()
                        messages.add_message("system", parallel_prompt)
                        messages.add_message("user", optimized_code)
                        optimized_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                        match = re.search(r'```cpp\s*(.*?)\s*```', optimized_code, re.DOTALL)
                        optimized_code = match.group(1).strip() if match else "No code found."
                        #optimized_code = re.sub(r'```cpp|```', '', optimized_code).strip()

                        if args.check:
                            # check compile
                            print("do check")
                            prefix = prefix + "check_"
                            compile_max_retry = args.check_max_retry
                            for _ in range (compile_max_retry):
                                compile_success, compile_message, function_success, function_message = compile_and_check(optimized_code, query_code)
                                if not compile_success or not function_success:
                                    if not compile_success:
                                        error_message = compile_message
                                    else:
                                        error_message = function_message
                                    prompt_for_correction = f"Here is an message of the optimized code:\nError: {error_message}\nPlease fix the code and regenerate the code."
                                    
                                    # Send error to LLM for correction
                                    messages.add_message("assistant", optimized_code)
                                    messages.add_message("user", prompt_for_correction)
                                    
                                    # Get the corrected code from LLM
                                    corrected_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                                    match = re.search(r'```cpp\s*(.*?)\s*```', corrected_code, re.DOTALL)
                                    optimized_code = match.group(1).strip() if match else "No code found."
                                    #optimized_code = re.sub(r'```cpp|```', '', corrected_code).strip()

                                else:
                                    break
                    elif (args.serial_rag) and (not args.parallel_rag):
                        print("serial rag then parallel")
                        prefix = "serial_rag_parallel_norag_"
                        optimizer_prompt = generate_rag_prompt(
                            problem, 
                            query_embedding, # 待查询问题embedding
                            s_faiss_index, # 知识库的embedding集合
                            s_target_to_problem_id, # code对应的problem id
                            s_training_data_target, 
                            False,
                            s_fast_src_to_tgt, # problem_id 对应的最高的前10%中随机的record
                            is_parallel=False
                        )
                        messages = MessageHistory()
                        messages.add_message("system", optimizer_prompt)
                        messages.add_message("user", json.dumps({"solution.cpp": problem.source_code}))
                        optimized_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                        match = re.search(r'```cpp\s*(.*?)\s*```', optimized_code, re.DOTALL)
                        optimized_code = match.group(1).strip() if match else "No code found."
                        #optimized_code = re.sub(r'```cpp|```', '', optimized_code).strip()
                        if args.check:
                            # check compile
                            print("do check")
                            # prefix = prefix + "check_"
                            compile_max_retry = args.check_max_retry
                            for _ in range (compile_max_retry):
                                compile_success, compile_message, function_success, function_message = compile_and_check(optimized_code, query_code)
                                if not compile_success or not function_success:
                                    if not compile_success:
                                        error_message = compile_message
                                    else:
                                        error_message = function_message
                                    prompt_for_correction = f"Here is an message of the optimized code:\nError: {error_message}\nPlease fix the code and regenerate the code."
                                    
                                    # Send error to LLM for correction
                                    messages.add_message("assistant", optimized_code)
                                    messages.add_message("user", prompt_for_correction)
                                    
                                    # Get the corrected code from LLM
                                    corrected_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                                    match = re.search(r'```cpp\s*(.*?)\s*```', corrected_code, re.DOTALL)
                                    optimized_code = match.group(1).strip() if match else "No code found."
                                    #optimized_code = re.sub(r'```cpp|```', '', corrected_code).strip()
                                else:
                                    break
            
                        messages = MessageHistory()
                        messages.add_message("system", parallel_prompt)
                        messages.add_message("user", optimized_code)
                        optimized_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                        match = re.search(r'```cpp\s*(.*?)\s*```', optimized_code, re.DOTALL)
                        optimized_code = match.group(1).strip() if match else "No code found."
                        #optimized_code = re.sub(r'```cpp|```', '', optimized_code).strip()
                        if args.check:
                            # check compile
                            print("do check")
                            prefix = prefix + "check_"
                            compile_max_retry = args.check_max_retry
                            for _ in range (compile_max_retry):
                                compile_success, compile_message, function_success, function_message = compile_and_check(optimized_code, query_code)
                                if not compile_success or not function_success:
                                    if not compile_success:
                                        error_message = compile_message
                                    else:
                                        error_message = function_message
                                    prompt_for_correction = f"Here is an message of the optimized code:\nError: {error_message}\nPlease fix the code and regenerate the code."
                                    
                                    # Send error to LLM for correction
                                    messages.add_message("assistant", optimized_code)
                                    messages.add_message("user", prompt_for_correction)
                                    
                                    # Get the corrected code from LLM
                                    corrected_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                                    match = re.search(r'```cpp\s*(.*?)\s*```', corrected_code, re.DOTALL)
                                    optimized_code = match.group(1).strip() if match else "No code found."
                                    #optimized_code = re.sub(r'```cpp|```', '', corrected_code).strip()
                                else:
                                    break
                    elif (args.serial_rag) and (args.parallel_rag):
                        print("serial rag then parallel rag")
                        prefix = "serial_rag_parallel_rag_"
                        optimizer_prompt = generate_rag_prompt(
                            problem, 
                            query_embedding, # 待查询问题embedding
                            s_faiss_index, # 知识库的embedding集合
                            s_target_to_problem_id, # code对应的problem id
                            s_training_data_target, 
                            False,
                            s_fast_src_to_tgt, # problem_id 对应的最高的前10%中随机的record
                            is_parallel=False
                        )
                        messages = MessageHistory()
                        messages.add_message("system", optimizer_prompt)
                        messages.add_message("user", json.dumps({"solution.cpp": problem.source_code}))
                        optimized_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                        match = re.search(r'```cpp\s*(.*?)\s*```', optimized_code, re.DOTALL)
                        optimized_code = match.group(1).strip() if match else "No code found."
                        #optimized_code = re.sub(r'```cpp|```', '', optimized_code).strip()
                        if args.check:
                            # check compile
                            print("do check")
                            # prefix = prefix + "check_"
                            compile_max_retry = args.check_max_retry
                            for _ in range (compile_max_retry):
                                compile_success, compile_message, function_success, function_message = compile_and_check(optimized_code, query_code)
                                if not compile_success or not function_success:
                                    if not compile_success:
                                        error_message = compile_message
                                    else:
                                        error_message = function_message
                                    prompt_for_correction = f"Here is an message of the optimized code:\nError: {error_message}\nPlease fix the code and regenerate the code."
                                    
                                    # Send error to LLM for correction
                                    messages.add_message("assistant", optimized_code)
                                    messages.add_message("user", prompt_for_correction)
                                    
                                    # Get the corrected code from LLM
                                    corrected_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                                    match = re.search(r'```cpp\s*(.*?)\s*```', corrected_code, re.DOTALL)
                                    optimized_code = match.group(1).strip() if match else "No code found."
                                    #optimized_code = re.sub(r'```cpp|```', '', corrected_code).strip()
                                else:
                                    break
                        optimizer_prompt = generate_rag_prompt(
                            problem, 
                            query_embedding, # 待查询问题embedding
                            p_faiss_index, # 知识库的embedding集合
                            p_target_to_problem_id, # code对应的problem id
                            p_training_data_target, 
                            False,
                            p_fast_src_to_tgt, # problem_id 对应的最高的前10%中随机的record
                            is_parallel=True
                        )
                        
                        messages = MessageHistory()
                        messages.add_message("system", optimizer_prompt)
                        messages.add_message("user", optimized_code)
                        optimized_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                        match = re.search(r'```cpp\s*(.*?)\s*```', optimized_code, re.DOTALL)
                        optimized_code = match.group(1).strip() if match else "No code found."
                        #optimized_code = re.sub(r'```cpp|```', '', optimized_code).strip()
                        if args.check:
                            # check compile
                            print("do check")
                            prefix = prefix + "check_"
                            compile_max_retry = args.check_max_retry
                            for _ in range (compile_max_retry):
                                compile_success, compile_message, function_success, function_message = compile_and_check(optimized_code, query_code)
                                if not compile_success or not function_success:
                                    if not compile_success:
                                        error_message = compile_message
                                    else:
                                        error_message = function_message
                                    prompt_for_correction = f"Here is an message of the optimized code:\nError: {error_message}\nPlease fix the code and regenerate the code."
                                    
                                    # Send error to LLM for correction
                                    messages.add_message("assistant", optimized_code)
                                    messages.add_message("user", prompt_for_correction)
                                    
                                    # Get the corrected code from LLM
                                    corrected_code = get_response_with_retry(chatAPI, model_path, messages, json_format=False)
                                    match = re.search(r'```cpp\s*(.*?)\s*```', corrected_code, re.DOTALL)
                                    optimized_code = match.group(1).strip() if match else "No code found."
                                    #optimized_code = re.sub(r'```cpp|```', '', corrected_code).strip()
                                else:
                                    break
                    else:
                        print("Error in two_stage True")
                        return
                    
            

                problem_id = problem.problem_id
                # print(problem_id)
                
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
            time.sleep(3)
                
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
