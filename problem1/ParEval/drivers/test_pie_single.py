import tempfile
import json
import subprocess
import shlex
import os
from pathlib import Path
import pytest

def run_driver(gen_file: str, problem_sizes_file: str = "problem-sizes.json", run_timeout: int = 300, launch_configs: str = "launch-configs-speedcode.json") -> tuple:
    """
    运行驱动程序并返回结果。
    """
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
        
        return driver_info_dict, output, error

def create_generation_dict(problem_category: str, problem_unique_id: str, optimized_code: str, prompt: str = "", baseline: str = "") -> list:
    """
    创建生成代码的字典。
    """
    d = {
        "outputs": [optimized_code],
        "name": problem_unique_id,
        "problem_type": problem_category,
        "parallelism_model": "omp",
        "language": "cpp",
        "prompt": prompt,
        "baseline": [baseline]
    }
    return [d]

def get_modified_content(sub_path: str) -> str:
    """
    获取修改后的文件内容。
    """
    # 修改文件路径为相对于当前文件的路径
    current_file = Path(__file__).absolute()
    project_root = current_file.parent  # 当前文件所在目录
    file_path = project_root / 'cpp' / 'benchmarks' / 'pie' / sub_path / 'baseline.hpp'
    
    if not file_path.is_file():
        raise FileNotFoundError(f"File {file_path} does not exist!")
    
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    
    modified_content = content.replace('baseline', 'optbaseline')
    return modified_content

@pytest.mark.parametrize("problem_id, problem_category", [
    ("p02262_pie", "pie"),
    # 添加更多测试用例
])
def test_run_driver(problem_id, problem_category):
    """
    测试运行驱动程序。
    """
    optimized_code = get_modified_content(problem_id)
    gen_dict = create_generation_dict(problem_category, problem_id, optimized_code)

    with tempfile.NamedTemporaryFile(suffix=".json") as gen_f:
        with open(gen_f.name, "w") as f:
            json.dump(gen_dict, f, indent=4)
        
        driver_info_dict, driver_stdout, driver_stderr = run_driver(gen_f.name)
        
        # 验证 driver_info_dict 是否包含预期的字段
        assert isinstance(driver_info_dict, list), "driver_info_dict 应该是一个列表"
        assert len(driver_info_dict) > 0, "driver_info_dict 应该包含至少一个元素"
        assert "outputs" in driver_info_dict[0], "driver_info_dict 的第一个元素应包含 'outputs'"
        assert len(driver_info_dict[0]["outputs"]) > 0, "outputs 应该包含至少一个元素"

        # 提取运行信息
        run_info = driver_info_dict[0]["outputs"][0]
        output_dict = {
            "did_build": bool(run_info["did_build"]),
            "did_run": bool(run_info["did_all_run"]),
            "is_valid": bool(run_info["are_all_valid"]),
            "baseline_runtime": run_info["best_sequential_runtime"] or 0.0,
            "optimized_runtime": (
                float(run_info["runs"][0]["runtime"])
                if run_info["runs"] and run_info["runs"][0]["runtime"] is not None
                else run_info["best_sequential_runtime"] or 0.0
            ),
            "stdout": driver_stdout,
            "stderr": driver_stderr,
        }

        # 验证运行结果
        assert output_dict["did_build"], "代码未成功编译"
        assert output_dict["did_run"], "代码未成功运行"
        assert output_dict["is_valid"], "代码运行结果无效"

        # 打印输出以供调试
        print("output_dict: ", output_dict)