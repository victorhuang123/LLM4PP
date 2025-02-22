## Fetch RAG dataset via `git-lfs`

```
git lfs install
git lfs pull
```

## **Start local API using vLLM**
**Pick a model to serve local API for evaluation**
- If your GPU has plenty of VRAM, we recommend serve unquantized models:
```shell
export CUDA_VISIBLE_DEVICES=0

## To evaluate Qwen2.5-Coder-32B-Instruct
nohup vllm serve Qwen/Qwen2.5-Coder-32B-Instruct --port 8001 --dtype bfloat16 --served-model-name local_model --max_model_len 16384 >> vllm.log 2>&1 &

## To evaluate Qwen2.5-Coder-14B-Instruct
nohup vllm serve Qwen/Qwen2.5-Coder-14B-Instruct --port 8001 --dtype bfloat16 --served-model-name local_model --max_model_len 16384 >> vllm.log 2>&1 &
```

- If your GPU has 24GB VRAM, please consider serve AWQ (w4a16) models:

```shell
export CUDA_VISIBLE_DEVICES=0

# To evaluate Qwen2.5-Coder-32B-Instruct
nohup vllm serve Qwen/Qwen2.5-Coder-32B-Instruct-AWQ --port 8001 --dtype half --quantization awq --served-model-name local_model --max_model_len 16384 >> vllm.log 2>&1 &

# To evaluate Qwen2.5-Coder-14B-Instruct
nohup vllm serve Qwen/Qwen2.5-Coder-14B-Instruct-AWQ --port 8001 --dtype half --quantization awq --served-model-name local_model --max_model_len 16384 >> vllm.log 2>&1 &
```

## **Generate optimized codes**

```shell
# Set API endpoint to the vLLM server
export OPENAI_BASE_URL="http://localhost:8001/v1"

# Generate codes to `./logs/local_model`
bash run.sh
```

## **Evaluate optimized codes**
```
bash eval.sh
```
