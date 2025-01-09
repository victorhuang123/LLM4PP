import csv

# 读取文件内容
def read_file(file_path):
    with open(file_path, "r") as file:
        lines = file.readlines()
    return lines

# 解析文件内容并提取 category 和 geomean speedup
def parse_data(lines):
    data = []
    is_header = True  # 标记是否为表头行
    for line in lines:
        # 提取数据行
        if "|" in line:
            if is_header:
                is_header=False
                continue
            parts = line.split("|")
            # print(len(parts))
            if len(parts) >= 5:  # 确保是数据行
                category = parts[1].strip()
                speedup = parts[4].strip()
                # print(speedup)
                data.append((category, float(speedup)))
    return data

def print_category_speedup(data):
    for category, speedup in data:
        print(f"{category},{speedup}")

# 将结果保存到CSV文件
def save_to_csv(data, output_file):
    with open(output_file, "w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["category", "geomean speedup"])  # 写入表头
        writer.writerows(data)  # 写入数据

# 主函数
def main(file_path, output_csv):
    # 读取文件
    lines = read_file(file_path)
    # 解析数据
    data = parse_data(lines)
    print(data)
    # 打印每一行：category,speedup
    print("打印结果：")
    print_category_speedup(data)
    # 保存到CSV文件
    save_to_csv(data, output_csv)
    print(f"\n结果已保存到文件：{output_csv}")

# 文件路径
file_path = "out"  # 输入文件路径
output_csv = "output.csv"  # 输出CSV文件路径
# 运行主函数
main(file_path, output_csv)