import os
import shutil
import subprocess
import tempfile
import pytest

def process_files(source_dir, debug=False):
    if debug:
        temp_folder = "./tmp"
        os.makedirs(temp_folder, exist_ok=True)
    else:
        temp_dir = tempfile.TemporaryDirectory()
        temp_folder = temp_dir.name

    try:
        # 1. 复制 cpu.cc 文件
        cpu_source = os.path.join(source_dir, "cpu.cc")
        if os.path.isfile(cpu_source):
            cpu_dest = os.path.join(temp_folder, "cpu.cc")
            shutil.copy2(cpu_source, cpu_dest)
        
        # 2.1 修改为在 #include 之后添加 namespace baseline
        def add_namespace_after_includes(content, namespace_name):
            lines = content.split('\n')
            insert_pos = 0
            for i, line in enumerate(lines):
                if line.strip().startswith('#include'):
                    insert_pos = i + 1
            result_lines = lines[:insert_pos]
            result_lines.append(f"\nnamespace {namespace_name} {{")
            result_lines.extend(lines[insert_pos:])
            result_lines.append(f"}} // namespace {namespace_name}")
            return '\n'.join(result_lines)

        # 处理 baseline.hpp 文件
        baseline_source = os.path.join(source_dir, "baseline.hpp")
        if os.path.isfile(baseline_source):
            with open(baseline_source, 'r') as f:
                content = f.read()
            baseline_content = add_namespace_after_includes(content, "baseline")
            baseline_dest = os.path.join(temp_folder, "baseline.hpp")
            with open(baseline_dest, 'w') as f:
                f.write(baseline_content)
            generated_content = add_namespace_after_includes(content, "generated")
            generated_dest = os.path.join(temp_folder, "generated-code.hpp")
            with open(generated_dest, 'w') as f:
                f.write(generated_content)
        
        # 3. 编译
        a_out_path = os.path.join(temp_folder, "a.out")
        compile_command = f"g++ -std=c++20 -O3 -I./tests -DDRIVER_PROBLEM_SIZE=\"(1<<9)\" -Icpp -Icpp/models -I{temp_folder} -DUSE_OMP -fopenmp cpp/models/omp-driver.o {temp_folder}/cpu.cc -o {a_out_path}"
        current_dir = os.path.dirname(os.path.abspath(__file__))  # 获取当前文件目录
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
            temp_dir.cleanup()
            shutil.rmtree(temp_folder, ignore_errors=True)

def get_all_problem_paths(base_dir):
    # 获取当前文件的绝对路径
    current_dir = os.path.dirname(os.path.abspath(__file__))
    benchmarks_dir = os.path.join(current_dir, base_dir, "cpp", "benchmarks")
    if not os.path.isdir(benchmarks_dir):
        print(f"错误: 指定的目录 {benchmarks_dir} 不存在!")
        return []
    problem_paths = []
    for category in os.listdir(benchmarks_dir):
        category_path = os.path.join(benchmarks_dir, category)
        if os.path.isdir(category_path):
            for problem in os.listdir(category_path):
                problem_path = os.path.join(category_path, problem)
                if os.path.isdir(problem_path):
                    problem_paths.append(problem_path)
    return problem_paths

@pytest.mark.parametrize("problem_path", get_all_problem_paths("."))
def test_process_files(problem_path):
    assert os.path.isdir(problem_path), f"问题路径 {problem_path} 不存在或不是目录"
    result = process_files(problem_path)
    assert result, f"问题 {problem_path.split('/')[-1]} 的验证失败!"
