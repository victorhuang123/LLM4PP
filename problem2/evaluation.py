from client.models import LLM4PP_Problem, LLM4PP_Submission
from client.pareval_client import ParEvalDriver
import json
import multiprocessing
import os
import glob
import argparse

def evaluate(json_file, eval_times, output_dir):
    print(json_file, eval_times, output_dir)
    with open(json_file, "r") as f:
        results = json.load(f)

    for run in range(eval_times):
        driver = ParEvalDriver()
        for problem in driver:
            problem : LLM4PP_Problem
            problem_id = problem.problem_id
            #print(f"Processing problem {problem_id} from {jsonl_file}")

            optimized_code = results.get(problem_id)

            submission = LLM4PP_Submission(problem=problem,
                                        submitted_code=optimized_code)
            try:
                response = driver.submit(submission)
                print(response)
                # response_dict[problem_id] = response
            except Exception as e:
                print(f"skipping problem due to exception: {e}")
                print("--- ParEval driver stdout ---")
                print(response.stdout)

        output_name = os.path.basename(json_file).replace(".json","") + f'_eval{run}' +'.json'
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        driver.save_all_responses(output_dir + output_name)
        driver.evaluate()

def evaluate_wrapper(args):
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
        "--processes",
        type=int,
        default="10",
        help="The size of the process pool used for testing."
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
    processes = args.processes
    eval_times = args.eval_times
    
    # change the path 
    json_files = glob.glob(os.path.join(codes_dir, '*.json'))
    tasks = [(json_file, eval_times, output_dir) for json_file in json_files]
    print(json_files)

    #TODO:Bind cores
    with multiprocessing.Pool(processes=processes) as pool:
        pool.map(evaluate_wrapper, tasks)

if __name__ == "__main__":
    main()