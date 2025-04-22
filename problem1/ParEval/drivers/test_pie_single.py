import tempfile
import json
import subprocess
import shlex
import os
from pathlib import Path
def run_driver(gen_file: str, problem_sizes_file: str = "problem-sizes.json", run_timeout: int = 300, launch_configs: str = "launch-configs-speedcode.json") -> str:
    # delete set to False as need this file in another function
    with tempfile.NamedTemporaryFile(suffix=".json") as output_f:
        args = f"python run-all.py {gen_file} -o {output_f.name} --yes-to-all --problem-sizes {problem_sizes_file} --run-timeout {run_timeout} --launch-configs {launch_configs}"

        current_file = Path(__file__).absolute()
        project_root = current_file.parent
        default_path = project_root 
        
        subprocess_args = shlex.split(args)
        proc = subprocess.run(subprocess_args, cwd=default_path, capture_output=True, text=True)
        output, error = proc.stdout, proc.stderr
       
        if proc.returncode != 0:
            print(f"output: {output}")
            print(f"error: {error}")

        with open(output_f.name) as driver_f:
            driver_info_dict = json.load(driver_f)
        # print(type(output))
        print(output)
        # print(driver_info_dict)
        return driver_info_dict, output, error

def create_generation_dict(problem_category: str, problem_unique_id: str, optimized_code: str, prompt: str = "", baseline: str = ""):
    d = {}
    d["outputs"] = []
    d["outputs"].append(optimized_code)
    d["name"] = problem_unique_id
    # extract problem type. Ex: 17_graph_highest_degree -> graph
    d["problem_type"] = problem_category
    d["parallelism_model"] = "omp"
    d["language"] = "cpp"
    d["prompt"] = prompt
    d["baseline"] = []
    d["baseline"].append(baseline)
    return [d]

def get_modified_content(sub_path):
    # 构建目标文件的路径
    # file_path = os.path.join('cpp', 'benchmarks', 'pie_back', sub_path, 'baseline.hpp')
    file_path = os.path.join('cpp', 'benchmarks', 'pie', sub_path, 'baseline.hpp')
    
    # 检查文件是否存在
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"File {file_path} does not exist!")
    
    # 读取文件内容
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    
    # 替换 'baseline' 为 'optbaseline'
    modified_content = content.replace('baseline', 'optbaseline')
    
    # 返回修改后的内容
    return modified_content

optimized_code = "#pragma once\n#include <array>\n#include <vector>\n\n/* Vector x contains values between 0 and 100, inclusive. Count the number of\n   values in [0,10), [10, 20), [20, 30), ... and store the counts in `bins`.\n   Example:\n\n   input: [7, 32, 95, 12, 39, 32, 11, 71, 70, 66]\n   output: [1, 2, 0, 3, 0, 0, 1, 2, 0, 1]\n*/\nvoid NO_INLINE binsBy10Count(const std::vector<double>& x, std::array<size_t, 10>& bins) {\n    bins.fill(0); // Ensure all bins start at 0\n    for (const auto& val : x) {\n        const size_t bin = static_cast<size_t>(val / 10);\n        if (bin < 10) { // Safety check in case val is exactly 100.0\n            ++bins[bin];\n        }\n    }\n}\n\n#if defined(USE_CUDA)\n// fix the issue where atomicAdd is not defined for size_t\nstatic_assert(sizeof(size_t) == sizeof(unsigned long long), \"size_t is not 64 bits\");\n\n__device__ __forceinline__ void atomicAdd(size_t* address, size_t val) {\n    atomicAdd(reinterpret_cast<unsigned long long*>(address), val);\n}\n#endif"
problem_id = "p02262_pie"
problem_category = "pie"
optimized_code = get_modified_content(problem_id)

# problem_id="21_histogram_bin_0-100"
# problem_category = "histogram" 
gen_dict = create_generation_dict(problem_category, problem_id, optimized_code)
# gen_dict = create_generation_dict("graph", "17_graph_highest_degree", optimized_code)
with tempfile.NamedTemporaryFile(suffix=".json") as gen_f:
    with open(gen_f.name, "w") as f:
        json.dump(gen_dict, f, indent=4)
    driver_info_dict, driver_stdout, driver_stderr = run_driver(gen_f.name)
    # print(driver_info_dict)
output_dict = {}

# assume length of outputs is 1 as only test 1 output at a time
# run_info = driver_info_dict[0]["outputs"][0]

# output_dict["did_build"] = bool(run_info["did_build"])
# output_dict["did_run"] = bool(run_info["did_all_run"])
# output_dict["is_valid"] = bool(run_info["are_all_valid"])
# baseline_runtime = run_info["best_sequential_runtime"]
# if baseline_runtime is None:
#     baseline_runtime = 0.0

# output_dict["baseline_runtime"] = baseline_runtime
# # code did not compile or code did not run without errors
# if run_info["runs"] is None or run_info["runs"][0]["runtime"] is None:
#     output_dict["optimized_runtime"] = baseline_runtime
# else:
#     output_dict["optimized_runtime"] = float(run_info["runs"][0]["runtime"])

# output_dict["stdout"] = driver_stdout
# output_dict["stderr"] = driver_stderr

# print("output_dict: ", output_dict)