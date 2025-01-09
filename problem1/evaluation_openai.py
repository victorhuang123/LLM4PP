from client.models import LLM4PP_Problem, LLM4PP_Submission
from client.pareval_client import ParEvalDriver
from fastcoder.chatapi import MessageHistory, ChatAPI
import json
import time

from sentence_transformers import SentenceTransformer
import torch
import json
from tqdm import tqdm
import numpy as np


num_top_matches = 1
inter_example_sep = "\n\n\n\n\n"

optimizer_prompt ="""You are a coding expert that writes very fast code. You write parallel C and C++ code using OpenMP and always strive to make the code as fast as possible. The user will give you code and you will provide a modified version of the user's code that is as fast as possible.

# Prompt format

The user will provide you a JSON dictionary in the following format:

```json
{
    "source_code" : <Initial code>
}
```

# Response format

You will respond with a JSON dictionary in the following format:

```json
{
    "updated_code" : <Optimized code>
}
```
"""
from tenacity import retry, stop_after_attempt, wait_exponential

@retry(stop=stop_after_attempt(3), wait=wait_exponential(multiplier=1, min=4, max=10))
def get_response_with_retry(chatAPI, model, messages, json_format=True):
    return chatAPI.get_response(model, messages, json_format)

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
    for start_idx in tqdm(range(0, len(texts), batch_size)):
        batch_texts = texts[start_idx:start_idx+batch_size]

        # Compute embeddings for the current batch and extend the list of embeddings
        embeddings.extend(model.encode(batch_texts, show_progress_bar=False))

    return np.array(embeddings)
def make_prompt(src_code, tgt_code):
    """
    Make a prompt for a given pair of codes.
    """
    prompt = f"""# slower version:

{src_code}


# optimized version of the same code:

{tgt_code}"""

    return prompt

def _make_query(prompt, slow_code):
  prompt = f"""{prompt}

# slower version:

{slow_code}

# optimized version of the same code:"""
  return prompt

import re
def canonicalize_newlines(code: str) -> str:
    """
    Canonicalize multiple newlines to a single newline
    """

    # call clang-format to canonicalize newlines

    return re.sub(r"\n+", "\n", code)

model = SentenceTransformer("neulab/codebert-cpp")  # just as an example
device = torch.device("cuda:0")
model.to(device)
print("model loaded")
json_path = "./data/PIE_Dataset/train.jsonl"
training_data = load_jsonl_data(json_path)
print("data loaded")
training_data_src = list(set([x["src_code"] for x in training_data]))
# src_embeddings = encode_in_batches(training_data_src, model, batch_size=128)
# np.save('src_embeddings.npy', src_embeddings)
src_embeddings = np.load('src_embeddings.npy')

print("finish embedding")
import faiss
dimension = src_embeddings.shape[1]  # Get the size of the embedding
faiss_index = faiss.IndexFlatL2(dimension)
faiss_index.add(np.array(src_embeddings).astype('float32'))

driver = ParEvalDriver()
chatAPI = ChatAPI()

for problem in driver:
    problem : LLM4PP_Problem
    
    query_code = problem.source_code
    
    top_matches = []
    query_embedding = model.encode(query_code).astype('float32')
    distances, indices = faiss_index.search(np.array([query_embedding]), num_top_matches)
    top_matches.append(indices)
    
    src_to_tgt = {}
    slow_code_to_prompt = {}

    for record in training_data:
        src_code = record['src_code']
        tgt_code = record['tgt_code']
        speedup = record['speedup']

        if src_code not in src_to_tgt or speedup > src_to_tgt[src_code]['speedup']:
            src_to_tgt[src_code] = record
            slow_code_to_prompt[src_code] = make_prompt(canonicalize_newlines(src_code), canonicalize_newlines(tgt_code))

    top_matches_pairs = []  # pair of (slow, fast)

    top_matches_i = top_matches[0][0]
    closest_slow_codes = [training_data_src[idx] for idx in top_matches_i]
    closest_prompts = [slow_code_to_prompt[src_code] for src_code in closest_slow_codes]

    _prompt = _make_query(inter_example_sep.join(closest_prompts[::-1]), query_code)
    # print(prompt)
    # exit(0)
    
    # optimizer_prompt = optimizer_prompt + "\n\n" + _prompt
    max_retries = 3
    retry_count = 0
    
    messages = MessageHistory()
    messages.add_message("system", optimizer_prompt)
    messages.add_message("user", json.dumps({"solution.cpp": problem.source_code}))
    response = get_response_with_retry(chatAPI, 'gpt-4o-mini', messages, json_format=True)
    response_dict = json.loads(response)
    
    while retry_count < max_retries:
        if 'updated_code' in response_dict:
            break 
        try:     
            # 获取 GPT 的响应
            # response = chatAPI.get_response('gpt-4o-mini', messages, json_format=True)
            response = get_response_with_retry(chatAPI, 'gpt-4o-mini', messages, json_format=True)

            # 解析响应为字典
            response_dict = json.loads(response)
            
            # 检查是否包含 'updated_code'
            if 'updated_code' in response_dict:
                break  
            else:
                print(f"Response does not contain 'updated_code'. Retrying... (Attempt {retry_count + 1}/{max_retries})")
                retry_count += 1
        except json.JSONDecodeError as e:
            print(f"Failed to decode JSON response: {e}. Retrying... (Attempt {retry_count + 1}/{max_retries})")
            retry_count += 1
        except Exception as e:
            print(f"An error occurred: {e}. Retrying... (Attempt {retry_count + 1}/{max_retries})")
            retry_count += 1
            
    optimized_code = response_dict['updated_code']
    print("problem: ", problem)
    print("response", response)
    # optimized_code = json.loads(response)['updated_code']

    submission = LLM4PP_Submission(problem=problem,
                                   submitted_code=optimized_code)

    try:
        response = driver.submit(submission)
    except Exception as e:
        print(f"skipping problem due to exception: {e}")
        print("--- ParEval driver stdout ---")
        print(response.stdout)
        
    time.sleep(5)


driver.save_all_responses("./tmp-pareval-results.json")
driver.evaluate()
print(chatAPI.get_cost())


# Example output
#"""
#+-----------+------------+-------------+-----------------+
#|  category | % compiled | correctness | geomean speedup |
#+-----------+------------+-------------+-----------------+
#|   graph   |    1.00    |     0.60    |       1.09      |
#| histogram |    1.00    |     1.00    |       4.69      |
#|    scan   |    1.00    |     0.40    |       1.26      |
#| transform |    0.80    |     0.80    |       1.19      |
#| sparse_la |    1.00    |     0.80    |       2.63      |
#|   reduce  |    1.00    |     1.00    |       5.50      |
#|    fft    |    1.00    |     0.60    |       1.69      |
#|  geometry |    1.00    |     0.60    |       1.23      |
#|  stencil  |    1.00    |     1.00    |       2.84      |
#|  dense_la |    1.00    |     1.00    |       2.37      |
#|    sort   |    0.80    |     0.40    |       1.00      |
#|   search  |    0.80    |     0.60    |       1.12      |
#|    all    |    0.95    |     0.73    |       1.86      |
#+-----------+------------+-------------+-----------------+
#"""


