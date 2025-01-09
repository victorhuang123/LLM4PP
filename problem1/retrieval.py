from sentence_transformers import SentenceTransformer
import torch
import json
from tqdm import tqdm
import numpy as np
def make_prompt(src_code, tgt_code):
    """
    Make a prompt for a given pair of codes.
    """
    prompt = f"""# slower version:

{src_code}


# optimized version of the same code:

{tgt_code}"""

    return prompt

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


model = SentenceTransformer("neulab/codebert-cpp")  # just as an example
device = torch.device("cuda:0")
model.to(device)

# json path
json_path = "./data/PIE_Dataset/train.jsonl"
training_data = load_jsonl_data(json_path)

training_data_src = list(set([x["src_code"] for x in training_data]))
src_embeddings = encode_in_batches(training_data_src, model, batch_size=128)

import faiss
dimension = src_embeddings.shape[1]  # Get the size of the embedding
faiss_index = faiss.IndexFlatL2(dimension)
faiss_index.add(np.array(src_embeddings).astype('float32'))