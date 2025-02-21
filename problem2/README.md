## **git lfs**

```
git lfs install
git lfs pull
```

## **Start local API using vLLM**

```shell
# Assign NVIDIA GPU device
export CUDA_VISIBLE_DEVICES=0

# If your GPU has enough VRAM, we recommend serve unquantized models

## To evaluate Qwen2.5-Coder-32B-Instruct:
nohup vllm serve Qwen/Qwen2.5-Coder-32B-Instruct --port 8001 --dtype bfloat16 --served-model-name local_model --max_model_len 16384 >> vllm.log 2>&1 &

## To evaluate Qwen2.5-Coder-14B-Instruct:
nohup vllm serve Qwen/Qwen2.5-Coder-14B-Instruct --port 8001 --dtype bfloat16 --served-model-name local_model --max_model_len 16384 >> vllm.log 2>&1 &

## To evaluate our fine-tuned Qwen2.5-PP-14B-Instruct:
nohup vllm serve MeowFET/Qwen2.5-PP-14B-Instruct  --port 8001 --dtype bfloat16 --served-model-name local_model --max_model_len 16384 >> vllm.log 2>&1 &

# If your GPU has 24GB VRAM, please consider serve AWQ (w4a16) models

# To evaluate Qwen2.5-Coder-32B-Instruct:
nohup vllm serve Qwen/Qwen2.5-Coder-32B-Instruct-AWQ --port 8001 --dtype half --quantization awq --served-model-name local_model --max_model_len 16384 >> vllm.log 2>&1 &

# To evaluate Qwen2.5-Coder-14B-Instruct:
nohup vllm serve Qwen/Qwen2.5-Coder-14B-Instruct-AWQ --port 8001 --dtype half --quantization awq --served-model-name local_model --max_model_len 16384 >> vllm.log 2>&1 &

# To evaluate our fine-tuned Qwen2.5-Coder-14B-Instruct model:
nohup vllm serve MeowFET/Qwen2.5-PP-14B-Instruct-AWQ --port 8001 --dtype half --quantization awq --served-model-name local_model --max_model_len 16384 >> vllm.log 2>&1 &
```

## **Generate optimized codes**

```shell
export OPENAI_BASE_URL="http://localhost:8001/v1"

# Generate codes to `./logs/local_model`
bash run.sh
```

## **Evaluate optimized codes**
```
bash eval.sh
```
