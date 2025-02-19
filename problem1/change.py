import json

# 定义文件路径
json_path_serial = "./json_file/serial.jsonl"
json_path_parallel = "./json_file/parallel.jsonl"

# 定义一个函数来读取 JSONL 文件并打印所有的键
def print_keys_from_jsonl(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        for line in file:
            # 解析每一行的 JSON 对象
            json_obj = json.loads(line.strip())
            # 打印所有的键
            print(f"Keys in {file_path}: {json_obj.keys()}")
            return

# 读取并打印 serial.jsonl 文件的所有键
print_keys_from_jsonl(json_path_serial)

# 读取并打印 parallel.jsonl 文件的所有键
print_keys_from_jsonl(json_path_parallel)