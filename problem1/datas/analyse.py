import os
import json
import pandas as pd
import re
from pathlib import Path
from scipy.stats import gmean

def process_json_files(json_file_paths):
        append_list = []
        for file_path in json_file_paths:
            parts = file_path.stem
            split = parts.rsplit('_',4)
            evaluate, generate, model, workmode = split[-1], split[-2], split[-4], split[-5]
            
            try:
                with open(file_path, 'r', encoding='utf-8') as file:
                    data = json.load(file)
            except Exception as e:
                print(f"Error loading {file_path}: {e}")
                continue

            for entry in data.get('responses', []):
                submission = entry.get('submission', {})
                problem = submission.get('problem', {})
                problem_id = problem.get('problem_id', None)
                compiled = entry.get('compiled', None)
                corrected = entry.get('correct', None)
                
                runtime = entry.get('runtime', 0)
                reference_runtime = entry.get('reference_runtime', 0)
                speedup = reference_runtime / runtime if runtime != 0 else 1
                
                unique_id = f"{parts}_{problem_id}"
                
                curr_result = {
                    'id': unique_id,
                    'workmode': workmode,
                    'model': model, 
                    'generate': generate,
                    'evaluate': evaluate,
                    'problem_id': problem_id,
                    'compiled': compiled,
                    'corrected': corrected,
                    'negative': speedup < 1,
                    'speedup': max(speedup, 1)
                }
                append_list.append(curr_result)
                
        return append_list

def main():
    # get all folders in datas
    root_dir = Path(__file__).resolve().parent
    try:
        subdirs = [entry.name for entry in root_dir.iterdir() if entry.is_dir()]
    except FileNotFoundError:
        print(f"Directory {root_dir} not found.")
        return
    except PermissionError:
        print(f"No permission to access {root_dir}.")
        return
        
    # init pandas
    pd_columns = ['id', 'workmode', 'model', 'generate', 'evaluate', 'problem_id', 'compiled', 'corrected', 'negative', 'speedup']
    df = pd.DataFrame(columns=pd_columns)
    


    if len(subdirs) == 0:
        json_file_paths = [f for f in root_dir.iterdir() if f.is_file() and f.suffix.lower() == '.json']
        append_list = process_json_files(json_file_paths)
        df = pd.concat([df, pd.DataFrame(append_list)], ignore_index=True)
    else:
        for model in subdirs:
            curr_dir = root_dir / model
            json_file_paths = [f for f in curr_dir.iterdir() if f.is_file() and f.suffix.lower() == '.json']
            append_list = process_json_files(json_file_paths)
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

    # 每一份代码最好的
    best_of_generate = sub1.groupby(['workmode', 'model', 'problem_id']).agg({
        'compiled': 'mean',
        'corrected': 'mean',
        'negative': 'mean',
        'speedup': 'max'
    }).reset_index()

    # 子表3：按前两列分组聚合
    sub3 = sub2.groupby(['workmode', 'model']).agg({
        'compiled': 'mean',
        'corrected': 'mean',
        'negative': 'mean',
        'speedup': gmean
    }).reset_index()
    
    best_of_workflow = best_of_generate.groupby(['workmode', 'model']).agg({
        'compiled': 'mean',
        'corrected': 'mean',
        'negative': 'mean',
        'speedup': gmean
    }).reset_index()
    
    best_of_workflow.rename(columns={'speedup': 'best_speedup'}, inplace=True)
    print(best_of_workflow)
    sub3_sorted = sub3.sort_values(by=['model'], key=lambda x: x.str.len())

        
    best_of_workflow_sorted = best_of_workflow.sort_values(by=['model'], key=lambda x: x.str.len())
    
    sub3_sorted['best_speedup'] = best_of_workflow_sorted['best_speedup']
    
    # 总表
    # 保存总表结果
    result = sub3_sorted
    with pd.ExcelWriter(root_dir / "results.xlsx") as writer:
        result.to_csv(root_dir / "results.csv", index=False)
        result.to_excel(writer, sheet_name="results", index=False)
        
        # 保存按问题分组的结果
        best_of_generate.to_csv(root_dir / "best_of_generate.csv", index=False)
        best_of_generate.to_excel(writer, sheet_name="best_of_each_problem", index=False)
    return

if __name__ == "__main__":
    main()
