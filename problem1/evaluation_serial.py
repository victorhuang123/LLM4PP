from client.models import LLM4PP_Problem, LLM4PP_Submission, BenchmarkDescription
from client.pareval_client import ParEvalDriver
import json
import multiprocessing
import os
import glob
import argparse
from pathlib import Path


def evaluate(problem_id, tgt_code):
    correct = [False, False, False]
    for run in range(3):
        driver = ParEvalDriver()
        category = ""
        parts = problem_id.split("_")
        all_categorys = [
            "dense_la",
            "geometry",
            "histogram",
            "scan",
            "sort",
            "stencil",
            "fft",
            "graph",
            "reduce",
            "search",
            "sparse_la",
            "transform",
        ]
        number = int(problem_id.split("_")[0])
        ccc = {'01', '09', '14', '19', '22', '27', '31', '36', '41', '47', '50', '55', '60', '61', '62', '63', '64', '65', '66', '67', '68', '69', '70', '71'}
        if number in ccc:
            return [problem_id, ""]
        for c in all_categorys:
            if c in problem_id:
                category = c
                break
        # category = parts[1]
        # category = "dense_la"
        problem = LLM4PP_Problem(
            problem_id=problem_id,
            source_code=tgt_code,
            category=category,
            header="",
            target_benchmark=BenchmarkDescription(num_cpus=1),
        )

        optimized_code = tgt_code
        submission = LLM4PP_Submission(problem=problem, submitted_code=optimized_code)
        try:
            response = driver.submit(submission)

        except Exception as e:
            print(f"skipping problem due to exception: {e}")
            print("--- ParEval driver stdout ---")
            print(response.stdout)
        print(response)
        correct[run] = response.correct

    if all(correct):
        return [problem_id, tgt_code]
    else:
        return [problem_id, ""]


def evaluate_wrapper(args):
    # return print_cpu_affinity(*args)
    return evaluate(*args)


def read_all_json_files(directory):
    json_data = []
    for json_file in Path(directory).rglob("*.json"):
        with open(json_file, "r", encoding="utf-8") as f:
            data = json.load(f)
            json_data.append(data)
    return json_data


def main():
    problem_id_set = set()
    json_datas = read_all_json_files("./synthesis/")
    tasks = []
    unique_tgt_code = set()
    for data in json_datas:
        for problem_id, tgt_code in data.items():
            if problem_id not in problem_id_set:
                problem_id_set.add(problem_id)
            if tgt_code in unique_tgt_code:
                continue
            unique_tgt_code.add(tgt_code)
            tasks.append((problem_id, tgt_code))
    print(len(unique_tgt_code))
    # tasks = [
    #    (
    #        "04_dense_la_gemv",
    #        "#pragma once\n#include <vector>\n\n/* \n * Performs matrix-vector multiplication y = A*x\n * A: MxN matrix in row-major order\n * x: Vector of size N\n * y: Output vector of size M (must be pre-allocated)\n * M: Number of rows in matrix A\n * N: Number of columns in matrix A\n * \n * Example:\n *   A = [[1, -1, 2], [0, -3, 1]] \n *   x = [2, 1, 0]\n *   Output y = [1, -3]\n */\nvoid NO_INLINE gemv(const std::vector<double>& A, \n                   const std::vector<double>& x, \n                   std::vector<double>& y, \n                   size_t M, size_t N) \n{\n    for (size_t row = 0; row < M; ++row) {\n        double sum = 0.0;\n        for (size_t col = 0; col < N; ++col) {\n            sum += A[row * N + col] * x[col];\n        }\n        y[row] = sum;\n    }\n}",
    #    )
    # ]
    # tasks = tasks[:1]
    dataset = {item: [] for item in problem_id_set}
    # print(tasks)
    with multiprocessing.Pool(processes=16) as pool:
        results = pool.map(evaluate_wrapper, tasks)

    count = 0
    for result in results:
        if result[1] != "":
            count += 1
            dataset[result[0]].append(result[1])
    print("All:", count)
    with open("./synthesis_data_new_generate.json", "w") as fw:
        json.dump(dataset, fw, indent=4)


if __name__ == "__main__":
    main()
