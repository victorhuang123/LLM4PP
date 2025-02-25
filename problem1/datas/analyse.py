import os
import json
import pandas as pd
import re
from pathlib import Path
from scipy.stats import gmean


def main():
    # get all folders in datas
    root_dir = Path(__file__).resolve().parent
    try:
        subdirs = [entry.name for entry in root_dir.iterdir() if entry.is_dir()]
    except FileNotFoundError:
        print(f"Directory {root_dir} not found.")
    except PermissionError:
        print(f"No permission to access {root_dir}.")
        
    # init pandas
    pd_columns = ['id', 'workmode', 'model', 'generate', 'evaluate', 'problem_id', 'compiled', 'corrected', 'negative', 'speedup']
    df = pd.DataFrame(columns=pd_columns)
    for model in subdirs:
        # get all json files
        curr_dir = root_dir / model
        json_file_paths = []
        for file_path in curr_dir.iterdir():
            if file_path.is_file() and file_path.suffix.lower() == '.json':
                json_file_paths.append(file_path.resolve())
                
        # 遍历每个文件并读取内容
        append_list = []
        for file_path in json_file_paths:
            # 一个工作流
            parts = file_path.stem
            split = parts.rsplit('_',4)
            evaluate = split[-1]
            generate = split[-2]
            model = split[-4]
            workmode = split[-5]
            # print(evaluate, generate, model, workmode)
            # return
            
            try:
                with open(file_path, 'r', encoding='utf-8') as file:
                    data = json.load(file)  # 直接解析 JSON 文件为字典
            except Exception as e:
                print(f"Error loading {file_path}: {e}")
                continue  # 跳过当前文件，继续下一个文件
            

            # 遍历 data 中的每一条记录（假设 data 是一个列表）
            for entry in data.get('responses', []):
                # print(entry)
                # 获取 submission 部分
                submission = entry.get('submission', {})
                problem = submission.get('problem', {})

                # 提取 problem_id
                problem_id = problem.get('problem_id', None)
                
                # 提取 compiled
                compiled = entry.get('compiled', None)
                
                # 提取 correct
                corrected = entry.get('correct', None)
                
                runtime = entry.get('runtime', 0)
                reference_runtime = entry.get('reference_runtime', 0)
                
                speedup = reference_runtime / runtime if runtime != 0 else 1
                
                unique_id = parts + '_' + problem_id
                # ['id', 'workmode', 'model', 'generate', 'evaluate', 'problem_id', 'compiled', 'corrected', 'negative', 'speedup']
    
                curr_result = {
                    'id': unique_id,
                    'workmode' : workmode,
                    'model': model,
                    'generate': generate,
                    'evaluate': evaluate,
                    'problem_id': problem_id,
                    'compiled': compiled, 
                    'corrected': corrected, 
                    'negative': False if speedup >= 1 else True,
                    'speedup': speedup if speedup >= 1 else 1
                }

                append_list.append(curr_result)


        df = pd.concat([df, pd.DataFrame(append_list)], ignore_index=True)

    # 子表1：按四列分组聚合
    sub1 = df.groupby(['workmode', 'model', 'generate', 'problem_id']).agg({
        'compiled': 'all',        # 全部True才为True
        'corrected': 'all',       # 同上
        'negative': 'mean',        # 求和
        'speedup': gmean          # 几何平均
    }).reset_index()

    # 子表2：按前三列分组聚合
    sub2 = sub1.groupby(['workmode', 'model', 'generate']).agg({
        'compiled': 'mean',
        'corrected': 'mean',
        'negative': 'mean',
        'speedup': gmean
    }).reset_index()

    # 子表3：按前两列分组聚合
    sub3 = sub2.groupby(['workmode', 'model']).agg({
        'compiled': 'mean',
        'corrected': 'mean',
        'negative': 'mean',
        'speedup': gmean
    }).reset_index()
    sub3_sorted = sub3.sort_values(by=['model'], key=lambda x: x.str.len())
    sub3_sorted.to_excel(root_dir / "results.xlsx", sheet_name="Sheet1", index=False)
    
    # df.to_parquet(root_dir / "datas.parquet")
    # print(df.head(3))
    return

if __name__ == "__main__":
    main()
