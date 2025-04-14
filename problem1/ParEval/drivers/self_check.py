import os
import shutil
import subprocess
import tempfile
import sys

def process_files(source_dir, debug=False):
    # 如果 debug 为 True，则使用 ./tmp 文件夹
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
            
            # 找到最后一个 #include 语句的位置
            for i, line in enumerate(lines):
                if line.strip().startswith('#include'):
                    insert_pos = i + 1
            
            # 在最后一个 include 后插入 namespace 开始
            result_lines = lines[:insert_pos]
            result_lines.append(f"\nnamespace {namespace_name} {{")
            result_lines.extend(lines[insert_pos:])
            result_lines.append(f"}} // namespace {namespace_name}")
            
            return '\n'.join(result_lines)

        # 处理 baseline.hpp 文件
        baseline_source = os.path.join(source_dir, "baseline.hpp")
        if os.path.isfile(baseline_source):
            # 读取原始文件内容
            with open(baseline_source, 'r') as f:
                content = f.read()
            
            # 2.1 用 namespace baseline 包裹
            baseline_content = add_namespace_after_includes(content, "baseline")
            baseline_dest = os.path.join(temp_folder, "baseline.hpp")
            with open(baseline_dest, 'w') as f:
                f.write(baseline_content)
            
            # 2.2 用 namespace generated 包裹
            generated_content = add_namespace_after_includes(content, "generated")
            generated_dest = os.path.join(temp_folder, "generated-code.hpp")
            with open(generated_dest, 'w') as f:
                f.write(generated_content)
        
        # 3. 编译，将 a.out 生成到临时文件夹中
        a_out_path = os.path.join(temp_folder, "a.out")
        compile_command = f"g++-14 -std=c++17 -O3 -I./tests -DDRIVER_PROBLEM_SIZE=\"(1<<9)\" -Icpp -Icpp/models -I{temp_folder} -DUSE_OMP -fopenmp cpp/models/omp-driver.o {temp_folder}/cpu.cc -o {a_out_path}"
        
        # 打印编译命令（仅在 debug 模式下）
        if debug:
            print(f"编译命令: {compile_command}")
        
        compile_result = subprocess.run(compile_command, shell=True, capture_output=True, text=True)
        
        # 检查编译是否成功
        if compile_result.returncode != 0:
            print("编译失败:")
            print(compile_result.stderr)
            return False
        
        # 4. 运行 a.out
        result = subprocess.run(f"{a_out_path} 8", shell=True, capture_output=True, text=True)
        if result.returncode != 0:
            print("运行失败:")
            print(result.stderr)
            return False

        output = result.stdout

        # 检查输出中是否包含 "Validation: PASS"
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
    # 遍历 ./cpp/benchmarks/ 下的所有 problem 文件夹
    benchmarks_dir = os.path.join(base_dir, "cpp", "benchmarks")
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


if __name__ == "__main__":
    problems = get_all_problem_paths(os.getcwd())
    
    all_correct = True
    for problem in problems:
        if os.path.isdir(problem):
            result = process_files(problem)
            if not result:
                all_correct = False
                print(f"问题 {problem.split('/')[-1]} 的验证失败!")
        else:
            print("错误: 指定的源目录不存在!")
    if all_correct:
        print("All PASS!")
# g++-14 -std=c++20 -v -O3 -I./tests -DDRIVER_PROBLEM_SIZE="(1<<9)" -Icpp -Icpp/models -I./tmp -DUSE_OMP -fopenmp cpp/models/omp-driver.o ./tmp/cpu.cc -o ./tmp/a.out