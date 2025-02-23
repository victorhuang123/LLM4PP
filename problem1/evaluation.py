from client.models import LLM4PP_Problem, LLM4PP_Submission
from client.pareval_client import ParEvalDriver
import json
import multiprocessing
import os
import glob
import argparse
import psutil

def get_bind_core_list():
    # get the map list from physic core to logic core
    core_map = {}
    with open('/proc/cpuinfo') as f:
        current_phys_id = None
        for line in f:
            # start a block
            if 'processor' in line:
                logical_id = int(line.split(':')[-1].strip())
                current_phys_id = None
            if 'core id' in line:
                current_phys_id = int(line.split(':')[-1].strip())
                if current_phys_id not in core_map:
                    core_map[current_phys_id] = []
                core_map[current_phys_id].append(logical_id)
                
    # get the bind list
    cores = [v[0] for _, v in sorted(core_map.items())]
    return [cores[i:i+8] for i in range(0, len(cores) // 8 * 8, 8)]

def init_worker(core_queue):
    core_list = core_queue.get()
    p = psutil.Process(os.getpid())
    p.cpu_affinity(core_list)

def print_cpu_affinity(json_file, eval_times, output_dir):
    try:
        # get list of current cpu affinity
        process = psutil.Process(os.getpid())
        affinity = process.cpu_affinity()
        output_name = os.path.basename(json_file).replace(".json","") +'.txt'
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        output_name = os.path.join(output_dir, output_name)
        
        with open(output_name, 'w') as fw:
            print(output_name, file=fw)
            print(affinity, file=fw)
            print(json_file, file=fw)
    except Exception as e:
        print(f"Get current cpu affinity failed: {e}")

def evaluate(json_file, eval_times, output_dir):
    with open(json_file, "r") as f:
        results = json.load(f)

    for run in range(eval_times):
        driver = ParEvalDriver()
        for problem in driver:
            problem : LLM4PP_Problem
            problem_id = problem.problem_id

            optimized_code = results.get(problem_id)

            submission = LLM4PP_Submission(problem=problem,
                                        submitted_code=optimized_code)
            try:
                response = driver.submit(submission)

            except Exception as e:
                print(f"skipping problem due to exception: {e}")
                print("--- ParEval driver stdout ---")
                print(response.stdout)

        output_name = os.path.basename(json_file).replace(".json","") + f'_eval{run}' +'.json'
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        output_name = os.path.join(output_dir, output_name)
        driver.save_all_responses(output_name)
        driver.evaluate()

def evaluate_wrapper(args):
    # return print_cpu_affinity(*args)
    return evaluate(*args)

def main():
    parser = argparse.ArgumentParser(description="Generate codes with ParEvalDriver.")
    parser.add_argument(
        "--codes-dir",
        type=str,
        default="./logs",
        help="Directory where generated codes be saved."
    )
    parser.add_argument(
        "--output-dir",
        type=str,
        default="./datas",
        help="Directory where evaluation results be saved."
    )
    parser.add_argument(
        "--eval-times",
        type=int,
        default="10",
        help="The number of tests per code."
    )
    args = parser.parse_args()
    codes_dir = args.codes_dir
    output_dir = args.output_dir
    eval_times = args.eval_times
    
    # change the path 
    json_files = glob.glob(os.path.join(codes_dir, '*.json'))
    tasks = [(json_file, eval_times, output_dir) for json_file in json_files]
    print(json_files)

    bind_core_lists = get_bind_core_list()
    pool_size = len(bind_core_lists)
    print(bind_core_lists)
    with multiprocessing.Manager() as manager:
        core_queue = manager.Queue()
        for core_lists in bind_core_lists:
            core_queue.put(core_lists)
            
        with multiprocessing.Pool(processes=pool_size, initializer=init_worker, initargs=(core_queue,)) as pool:
            pool.map(evaluate_wrapper, tasks)

if __name__ == "__main__":
    main()