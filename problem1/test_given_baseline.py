from client.models import LLM4PP_Problem, LLM4PP_Submission, BenchmarkDescription
from client.pareval_client import ParEvalDriver
import json
import multiprocessing
import os
import glob
import argparse
from pathlib import Path
import pytest

# For a given baseline, it can be evaluated in this way.

baseline_code = """
#pragma once
#include <vector>

/* Performs LU decomposition of matrix A in-place (Doolittle's method)
   A: NxN matrix stored in row-major order
   N: dimension of the square matrix
   Result is stored in A where:
   - Lower triangular part (including diagonal) contains L
   - Upper triangular part contains U
*/
void luFactorize(std::vector<double>& A, size_t N) 
{
    for (size_t pivot = 0; pivot < N; ++pivot) 
    {
        // Compute elements of L below the pivot
        for (size_t row = pivot + 1; row < N; ++row) 
        {
            double multiplier = A[row * N + pivot] / A[pivot * N + pivot];
            A[row * N + pivot] = multiplier;  // Store L coefficient
            
            // Update remaining elements in current row
            for (size_t col = pivot + 1; col < N; ++col) 
            {
                A[row * N + col] -= multiplier * A[pivot * N + col];
            }
        }
    }
}
"""
problem_id = "00_dense_la_lu_decomp"
baseline_code = """
#pragma once
#include <vector>

/* Performs LU decomposition of matrix A in-place (Doolittle's method)
    A: NxN matrix stored in row-major order
    N: dimension of the square matrix
    Result is stored in A where:
    - Lower triangular part (including diagonal) contains L
    - Upper triangular part contains U
*/
void luFactorize(std::vector<double>& A, size_t N) 
{
     for (size_t pivot = 0; pivot < N; ++pivot) 
     {
          // Compute elements of L below the pivot
          for (size_t row = pivot + 1; row < N; ++row) 
          {
                double multiplier = A[row * N + pivot] / A[pivot * N + pivot];
                A[row * N + pivot] = multiplier;  // Store L coefficient
                
                // Update remaining elements in current row
                for (size_t col = pivot + 1; col < N; ++col) 
                {
                     A[row * N + col] -= multiplier * A[pivot * N + col];
                }
          }
     }
}
"""

optimized_code = """
#pragma once
#include <vector>

/* 
Performs LU decomposition of a square matrix A in-place.
A is decomposed into A = LU where:
- L is a lower triangular matrix with unit diagonal
- U is an upper triangular matrix
The result is stored compactly in A where:
- The upper triangle (including diagonal) contains U
- The lower triangle (excluding diagonal) contains L's multipliers

Parameters:
- A: Reference to matrix data in row-major order (size N×N)
- N: Dimension of the square matrix
*/
void luFactorize(std::vector<double>& A, size_t N) 
{
     for (size_t pivot = 0; pivot < N; ++pivot) 
     {
          const size_t pivot_index = pivot * N + pivot;
          const double pivot_value = A[pivot_index];
          
          // 计算当前列的乘数因子
          for (size_t row = pivot + 1; row < N; ++row) 
          {
                const size_t element_index = row * N + pivot;
                A[element_index] /= pivot_value;
                
                // 更新剩余子矩阵
                for (size_t col = pivot + 1; col < N; ++col) 
                {
                     A[row * N + col] -= A[element_index] * A[pivot * N + col];
                }
          }
     }
}
"""

problem_id = "00_dense_la_lu_decomp"
category = "dense_la"

@pytest.fixture
def setup_problem():
     driver = ParEvalDriver()
     problem = LLM4PP_Problem(
          problem_id=problem_id,
          source_code=baseline_code,
          category=category,
          header="",
          target_benchmark=BenchmarkDescription(num_cpus=1),
     )
     return driver, problem

def test_submission_success(setup_problem):
     driver, problem = setup_problem
     submission = LLM4PP_Submission(problem=problem, submitted_code=optimized_code, baseline_code=baseline_code)
     try:
          response = driver.submit(submission)
          assert response is not None
          print(response)
     except Exception as e:
          pytest.fail(f"Submission failed with exception: {e}")

def test_submission_optimized_only(setup_problem):
    driver, problem = setup_problem
    submission = LLM4PP_Submission(problem=problem, submitted_code=optimized_code)
    try:
        response = driver.submit(submission)
        assert response is not None
        print(response)
    except Exception as e:
        pytest.fail(f"Baseline-only submission failed with exception: {e}")
        response = driver.submit(submission)
        print(response)
    except Exception as e:
        print(f"skipping problem due to exception: {e}")
        print("--- ParEval driver stdout ---")
        print(response.stdout)
        print(response)


if __name__ == "__main__":
    main()
