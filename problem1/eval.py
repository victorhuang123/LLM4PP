from client.models import LLM4PP_Problem, LLM4PP_Submission
from client.pareval_client import ParEvalDriver
import json

driver = ParEvalDriver()
# json_file = "opt_code/optimized_codes.json"
json_file = "opt_code/base.json"
results = {}

with open(json_file, "r") as f:
    results = json.load(f)
response_dict = {}
# print(results)    
for problem in driver:
    problem : LLM4PP_Problem
    problem_id = problem.problem_id
    print(problem_id)
    # print(results[problem_id])
    
    # TODO: do something to optimize the code.
    optimized_code = results[problem_id]
    submission = LLM4PP_Submission(problem=problem,
                                   submitted_code=optimized_code)
    try:
        response = driver.submit(submission)
        print(response)
        response_dict[problem_id] = response
    except Exception as e:
        print(f"skipping problem due to exception: {e}")
        print("--- ParEval driver stdout ---")
        print(response.stdout)

driver.save_all_responses("./tmp-pareval-results.json")
driver.evaluate()

# print(response_dict)
# response_dict
# output_file = "response_dict.json"
# with open(output_file, "w") as f:
#     json.dump(response_dict, f, indent=4)

