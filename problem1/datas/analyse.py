import os
import json
import pandas as pd
import re
from pathlib import Path
from scipy.stats import gmean
import numpy as np
import argparse
import argparse

# 
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
            category = problem.get('category', None)
            compiled = entry.get('compiled', None)
            corrected = entry.get('correct', None)
            
            runtime = entry.get('runtime', 0)
            reference_runtime = entry.get('reference_runtime', 0)
            speedup = reference_runtime / runtime if runtime != 0 else 1
            
            unique_id = f"{parts}_{problem_id}"
            if speedup < 1 and corrected and compiled:
                # 在测试中, 如果这一次speedup小于1, 且正确, 则记录为负优化
                negative = True
            else:
                negative = False
            
            curr_result = {
                'id': unique_id,
                'workmode': workmode,
                'model': model, 
                'generate': generate,
                'generate_id': int(generate[3:]),
                'evaluate': evaluate,
                'evaluate_id': int(evaluate[4:]),
                'problem_id': problem_id,
                'category': category,
                'compiled': compiled,
                'corrected': corrected,
                'negative': negative,
                # 负优化, 错误的代码加速比设置为1, 相当于0
                'speedup': max(speedup, 1)
            }
            append_list.append(curr_result)
            
    return append_list
        for entry in data.get('responses', []):
            submission = entry.get('submission', {})
            problem = submission.get('problem', {})
            problem_id = problem.get('problem_id', None)
            category = problem.get('category', None)
            compiled = entry.get('compiled', None)
            corrected = entry.get('correct', None)
            
            runtime = entry.get('runtime', 0)
            reference_runtime = entry.get('reference_runtime', 0)
            speedup = reference_runtime / runtime if runtime != 0 else 1
            
            unique_id = f"{parts}_{problem_id}"
            if speedup < 1 and corrected and compiled:
                # 在测试中, 如果这一次speedup小于1, 且正确, 则记录为负优化
                negative = True
            else:
                negative = False
            
            curr_result = {
                'id': unique_id,
                'workmode': workmode,
                'model': model, 
                'generate': generate,
                'generate_id': int(generate[3:]),
                'evaluate': evaluate,
                'evaluate_id': int(evaluate[4:]),
                'problem_id': problem_id,
                'category': category,
                'compiled': compiled,
                'corrected': corrected,
                'negative': negative,
                # 负优化, 错误的代码加速比设置为1, 相当于0
                'speedup': max(speedup, 1)
            }
            append_list.append(curr_result)
            
    return append_list



def calculate_group_stats(group):
    # 计算常规指标的算术平均
    compiled_mean = group['compiled'].mean()
    corrected_mean = group['corrected'].mean()
    negative_mean = group['negative'].mean()
    
    # 筛选符合条件的数据点 (compiled=True 且 corrected=True)
    valid_speedup = group[(group['compiled']) & (group['corrected'])]['speedup']
    
    # 计算几何平均或设置默认值
    speedup_geo_mean = gmean(valid_speedup) if not valid_speedup.empty else 1.0
    
    return pd.Series({
        'compiled': compiled_mean,
        'corrected': corrected_mean,
        'negative': negative_mean,
        'speedup': speedup_geo_mean
    })

# 对于同一道题的加速比, 使用算数平均
# 对于不同题的加速比, 使用几何平均


def calculate_group_stats(group):
    # 计算常规指标的算术平均
    compiled_mean = group['compiled'].mean()
    corrected_mean = group['corrected'].mean()
    negative_mean = group['negative'].mean()
    
    # 筛选符合条件的数据点 (compiled=True 且 corrected=True)
    valid_speedup = group[(group['compiled']) & (group['corrected'])]['speedup']
    
    # 计算几何平均或设置默认值
    speedup_geo_mean = gmean(valid_speedup) if not valid_speedup.empty else 1.0
    
    return pd.Series({
        'compiled': compiled_mean,
        'corrected': corrected_mean,
        'negative': negative_mean,
        'speedup': speedup_geo_mean
    })

# 对于同一道题的加速比, 使用算数平均
# 对于不同题的加速比, 使用几何平均

def main():
    parser = argparse.ArgumentParser()
    
    parser = argparse.ArgumentParser()
    
    # get all folders in datas
    parser.add_argument(
        "--data-dir",
        type=str,
        default="./"
    )
    args = parser.parse_args()
    data_dir = args.data_dir
    # root_dir = Path(__file__).resolve().parent
    root_dir = Path(data_dir)
    parser.add_argument(
        "--data-dir",
        type=str,
        default="./"
    )
    args = parser.parse_args()
    data_dir = args.data_dir
    # root_dir = Path(__file__).resolve().parent
    root_dir = Path(data_dir)
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

    # 对generate_id列进行切片并转换为整数
    df['generate_id'] = df['generate'].str[3:].astype(int)
    # 对evaluate_id列进行切片并转换为整数
    df['evaluate_id'] = df['evaluate'].str[4:].astype(int)
    
    # 每一份代码evaluate了多次, 将多次evaluate聚合为一次
    # 由于是同一份代码,所以compiled和corrected全true才true
    # 当compiled和corrected为true, 则为gmean, 否则是1
    avg_of_evaluate = df.groupby(['workmode', 'model', 'generate', 'generate_id', 'problem_id']).agg({
        'compiled': 'all',        # 全部True才为True
        'corrected': 'all',       # 同上
        'negative': 'mean',        # 求和
        'speedup': gmean          # 几何平均
    }).reset_index()
    # 同一次代码的多次evaluate, 如果有一次没通过, 则说明这份代码是错的
    avg_of_evaluate["speedup"] = np.where(
        (avg_of_evaluate["compiled"] & avg_of_evaluate["corrected"]),  # 条件：compiled 和 corrected 均为 True
        avg_of_evaluate["speedup"],                         # 满足条件时保留原值（即 gmean 结果）
        1                                        # 否则设为 1
    )
    
    # 由于要统计正确代码的平均加速比, 所以先挑出正确的代码
    
    
    # 由于要统计正确代码的平均加速比, 所以先挑出正确的代码
    
    
    # 每次generate的speedup, 是所有problem的avg
    avg_of_generate = avg_of_evaluate.groupby(['workmode', 'model', 'generate', 'generate_id']).agg({
        'compiled': 'mean',        
        'corrected': 'mean',       
        'negative': 'mean',        # 求和
        'speedup': gmean          # 几何平均
    }).reset_index()    
    # 取generate的topk
    avg_of_generate_sorted = avg_of_generate.sort_values(['workmode', 'model', 'generate_id'], ascending=[True, True, True])
    avg_of_generate_sorted['max_speedup'] = avg_of_generate_sorted.groupby(['workmode', 'model'])['speedup'].cummax()
    
    topk = avg_of_generate_sorted[['workmode', 'model', 'generate_id', 'speedup','max_speedup']].rename(
        columns={'max_speedup': 'topk'}
    )
    topk_col=[0,4,19,49,99]
    topk = topk.groupby(['workmode', 'model']).apply(lambda x: x[x['generate_id'].isin(topk_col)])
    # print(topk.head(10))
    
    # 对于一个workflow, 生成了多份代码, 这几份代码取均值
    avg_of_problem = avg_of_evaluate.groupby(['workmode', 'model', 'generate_id', 'generate']).agg({
        'compiled': 'mean',
        'corrected': 'mean',
        'negative': 'mean',
        'speedup': gmean
    }).reset_index()


    # 一个workflow里每个问题的best
    best_of_generate = avg_of_evaluate.groupby(['workmode', 'model', 'problem_id']).agg({
        'compiled': 'mean',
        'corrected': 'mean',
        'negative': 'mean',
        'speedup': 'max'
    }).reset_index()

    avg_of_generate = avg_of_evaluate.groupby(['workmode', 'model', 'problem_id']).apply(calculate_group_stats).reset_index()

    # 每个workflow所有代码的均值
    avg_of_workflow = avg_of_problem.groupby(['workmode', 'model']).agg(
        compiled=('compiled', 'mean'),        # 原列名 + 聚合函数后缀
        corrected=('corrected', 'mean'),
        negative=('negative', 'mean'),
        speedup_mean=('speedup', 'mean'),          # 显式命名 speedup 的均值
        speedup_gmean=('speedup', gmean)          # 显式命名 speedup 的几何平均
    ).reset_index()
    
    avg_of_avg_of_generate = avg_of_generate.groupby(['workmode', 'model']).agg(
        compiled=('compiled', 'mean'),        # 原列名 + 聚合函数后缀
        corrected=('corrected', 'mean'),
        negative=('negative', 'mean'),
        speedup_mean=('speedup', 'mean'),          # 显式命名 speedup 的均值
        speedup_gmean=('speedup', gmean)          # 显式命名 speedup 的几何平均
    ).reset_index()
    
    # 所有问题speedup的最高值
    best_of_workflow = best_of_generate.groupby(['workmode', 'model']).agg(
        compiled=('compiled', 'mean'),        # 原列名 + 聚合函数后缀
        corrected=('corrected', 'mean'),
        negative=('negative', 'mean'),
        speedup_mean=('speedup', 'mean'),          # 显式命名 speedup 的均值
        speedup_gmean=('speedup', gmean)          # 显式命名 speedup 的几何平均
    ).reset_index()
    best_of_workflow = best_of_generate.groupby(['workmode', 'model']).agg(
        compiled=('compiled', 'mean'),        # 原列名 + 聚合函数后缀
        corrected=('corrected', 'mean'),
        negative=('negative', 'mean'),
        speedup_mean=('speedup', 'mean'),          # 显式命名 speedup 的均值
        speedup_gmean=('speedup', gmean)          # 显式命名 speedup 的几何平均
    ).reset_index()
    
    
    # 为问题设置难度
    # 如果best speedup <= 2, 则难度为3
    # 如果2 < best speedup <= 8, 则难度为2
    # 如果8 < best speedup, 则难度为1
    # 首先取workmode='base'的数据
    base = best_of_generate[best_of_generate['workmode'] == 'base']
    base['difficulty'] = np.where(base['speedup'] <= 2, 3,
                                  np.where(base['speedup'] <= 8, 2, 1))
    # 将problem_id, difficulty保存到json文件中
    with open('problem_difficulty.json', 'w') as f:
        json.dump(base[['problem_id', 'difficulty']].to_dict(orient='records'), f)
    
    

    best_of_workflow.rename(columns={'speedup_mean': 'best_speedup_mean'}, inplace=True)
    best_of_workflow.rename(columns={'speedup_gmean': 'best_speedup_gmean'}, inplace=True)
    
    # print(best_of_workflow)
    avg_of_workflow_sorted = avg_of_workflow.sort_values(by=['model'], key=lambda x: x.str.len())

        
    
    best_of_workflow_sorted = best_of_workflow.sort_values(by=['model'], key=lambda x: x.str.len())
    print(best_of_workflow_sorted)
    avg_of_avg_of_generate = avg_of_avg_of_generate.sort_values(by=['model'], key=lambda x: x.str.len())
    print(best_of_workflow_sorted)
    avg_of_avg_of_generate = avg_of_avg_of_generate.sort_values(by=['model'], key=lambda x: x.str.len())
    
    avg_of_workflow_sorted['best_speedup_mean'] = best_of_workflow_sorted['best_speedup_mean']
    avg_of_workflow_sorted['best_speedup_gmean'] = best_of_workflow_sorted['best_speedup_gmean']
    avg_of_workflow_sorted['avg_positive_speedup_mean'] = avg_of_avg_of_generate['speedup_mean']
    avg_of_workflow_sorted['avg_positive_speedup_gmean'] = avg_of_avg_of_generate['speedup_gmean']
    avg_of_workflow_sorted['best_speedup_mean'] = best_of_workflow_sorted['best_speedup_mean']
    avg_of_workflow_sorted['best_speedup_gmean'] = best_of_workflow_sorted['best_speedup_gmean']
    avg_of_workflow_sorted['avg_positive_speedup_mean'] = avg_of_avg_of_generate['speedup_mean']
    avg_of_workflow_sorted['avg_positive_speedup_gmean'] = avg_of_avg_of_generate['speedup_gmean']
    # 总表
    # 保存总表结果
    result = avg_of_workflow_sorted
    with pd.ExcelWriter(root_dir / "a_results.xlsx") as writer:
        result.to_csv(root_dir / "results.csv", index=False)
        result.to_excel(writer, sheet_name="results", index=False)
        
        # 保存按问题分组的结果
        best_of_generate.to_csv(root_dir / "best_of_generate.csv", index=False)
        best_of_generate.to_excel(writer, sheet_name="best_of_each_problem", index=False)
        
        topk.to_csv(root_dir / "topk.csv", index=False)
        topk.to_excel(writer, sheet_name="topk_of_each_workflow", index=False)
        
        avg_of_avg_of_generate.to_csv(root_dir / "avg.csv", index=False)
        avg_of_avg_of_generate.to_excel(writer, sheet_name="avg_of_avg_of_generate", index=False)
        
        avg_of_generate.to_csv(root_dir / "avg_of_generate.csv", index=False)
    return

if __name__ == "__main__":
    main()
