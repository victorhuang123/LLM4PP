import os
import shutil
import subprocess
import tempfile
import pytest

def replace_baseline_with_optbaseline(content):
    """
    将baseline函数替换为optbaseline函数。
    """
    return content.replace("baseline(", "optbaseline(")

def remove_generateInput(content):
    """
    删除 generateInput 函数，无论其返回值类型为何。
    """
    lines = content.split('\n')
    result_lines = []
    in_generate_input = False
    brace_count = 0  # 用于跟踪大括号的嵌套层级

    for line in lines:
        stripped_line = line.strip()
        if not in_generate_input:
            # 检查是否是 generateInput 函数的定义
            if "generateInput" in stripped_line and "(" in stripped_line and ")" in stripped_line and "{" in stripped_line:
                in_generate_input = True
                brace_count = stripped_line.count('{') - stripped_line.count('}')
            else:
                result_lines.append(line)
        else:
            # 计算大括号的嵌套层级
            brace_count += stripped_line.count('{') - stripped_line.count('}')
            if brace_count == 0:  # 函数结束
                in_generate_input = False
        # 如果在 generateInput 函数内部，则跳过当前行

    return '\n'.join(result_lines)

def process_pie_problem(problem_id, debug=False):
    """
    处理 pie 相关问题的测试逻辑。
    """
    current_dir = os.path.dirname(os.path.abspath(__file__))  # 获取当前文件目录
    source_dir = os.path.join(current_dir, f"cpp/benchmarks/pie/{problem_id}_pie")
    if not os.path.isdir(source_dir):
        print(f"错误: 指定的目录 {source_dir} 不存在!")
        return False

    if debug:
        temp_folder = os.path.join(current_dir, "./tmp")
        os.makedirs(temp_folder, exist_ok=True)
    else:
        temp_dir = tempfile.TemporaryDirectory()
        temp_folder = temp_dir.name

    try:
        # 1. 复制 baseline.hpp 文件
        baseline_source = os.path.join(source_dir, "baseline.hpp")
        if not os.path.isfile(baseline_source):
            print(f"错误: baseline.hpp 文件不存在于 {source_dir}!")
            return False

        with open(baseline_source, 'r') as f:
            baseline_content = f.read()

        # 生成 generated-code.hpp 文件
        generated_content = replace_baseline_with_optbaseline(baseline_content)
        generated_content = remove_generateInput(generated_content)
        generated_dest = os.path.join(temp_folder, "generated-code.hpp")
        with open(generated_dest, 'w') as f:
            f.write(generated_content)

        # 复制 baseline.hpp 文件到临时目录
        baseline_dest = os.path.join(temp_folder, "baseline.hpp")
        baseline_content = remove_generateInput(baseline_content)
        with open(baseline_dest, 'w') as f:
            f.write(baseline_content)

        # 2. 复制 cpu.cc 文件
        cpu_source = os.path.join(source_dir, "cpu.cc")
        if not os.path.isfile(cpu_source):
            print(f"错误: cpu.cc 文件不存在于 {source_dir}!")
            return False

        cpu_dest = os.path.join(temp_folder, "cpu.cc")
        shutil.copy2(cpu_source, cpu_dest)

        # 3. 编译
        a_out_path = os.path.join(temp_folder, "a.out")
        compile_command = f"g++ -std=c++20 -O3 -I{os.path.join(current_dir, 'tests')} -I{os.path.join(current_dir, 'cpp')} -I{os.path.join(current_dir, 'cpp/models')} -I{temp_folder} -DDRIVER_PROBLEM_SIZE=\"(1<<9)\" -DUSE_OMP -fopenmp cpp/models/omp-driver.o {cpu_dest} -o {a_out_path}"
        if debug:
            print(f"编译命令: {compile_command}")
        compile_result = subprocess.run(compile_command, shell=True, capture_output=True, text=True, cwd=current_dir)
        if compile_result.returncode != 0:
            print("编译失败:")
            print(compile_result.stderr)
            return False

        # 4. 运行 a.out
        result = subprocess.run(f"{a_out_path} 8", shell=True, capture_output=True, text=True, cwd=current_dir)
        if result.returncode != 0:
            print("运行失败:")
            print(result.stderr)
            return False

        # 检查输出
        output = result.stdout
        for line in output.splitlines():
            if line.startswith("Validation:"):
                validation_status = line.split(":")[1].strip()
                if validation_status == "PASS":
                    return True
        print("验证失败: 未找到 'Validation: PASS'")
        return False
    finally:
        if not debug:
            shutil.rmtree(temp_folder, ignore_errors=True)

@pytest.mark.parametrize("problem_id", [
    'p03822', 'p04012', 'p03258', 'p02599', 'p04040', 'p02782', 'p03676', 'p02715', 
    'p03504', 'p03732', 'p03841', 'p03791', 'p00142', 'p03909', 'p02363', 'p00298', 
    'p03170', 'p03374', 'p03558', 'p02702', 'p03325', 'p03939', 'p00740', 'p04025', 
    'p03355', 'p02801', 'p01462', 'p03381', 'p00460', 'p02948', 'p02658', 'p03986', 
    'p00106', 'p02262', 'p02701'
])
# @pytest.mark.parametrize("problem_id", [
#     'p03504'
# ])
def test_process_pie_problem(problem_id):
    assert process_pie_problem(problem_id, debug=False), f"问题 {problem_id} 的验证失败!"