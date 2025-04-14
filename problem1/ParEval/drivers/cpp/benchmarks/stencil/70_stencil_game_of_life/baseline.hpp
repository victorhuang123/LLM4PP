#pragma once
#include <vector>

/* Simulate one generation of Game of Life on `input`. Store the results in `output`.
   A cell is 1 if it is alive and 0 if it is dead.
   If a live cell has fewer than 2 live neighbors then it dies.
   If a live cell has 2 or 3 live neighbors then it lives on.
   If a live cell has more than 3 live neighbords then it dies.
   If a cell is dead and has exactly 3 live neighbors then it becomes alive.
   `input` and `output` are NxN grids stored in row-major.
   Example:

   input:  [[0, 0, 0, 0, 0],
            [0, 1, 0, 0, 0],
            [0, 1, 1, 0, 0],
            [0, 0, 1, 1, 0],
            [0, 1, 0, 0, 0]]
   output: [[0, 0, 0, 0, 0],
            [0, 1, 1, 0, 0],
            [0, 1, 0, 1, 0],
            [0, 0, 0, 1, 0],
            [0, 0, 1, 0, 0]]
*/
void NO_INLINE gameOfLife(std::vector<int> const& input, std::vector<int> &output, size_t N) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            int sum = 0;
            if (i > 0) {
                sum += input[(i - 1) * N + j];
            }
            if (i < N - 1) {
                sum += input[(i + 1) * N + j];
            }
            if (j > 0) {
                sum += input[i * N + (j - 1)];
            }
            if (j < N - 1) {
                sum += input[i * N + (j + 1)];
            }
            if (i > 0 && j > 0) {
                sum += input[(i - 1) * N + (j - 1)];
            }
            if (i > 0 && j < N - 1) {
                sum += input[(i - 1) * N + (j + 1)];
            }
            if (i < N - 1 && j > 0) {
                sum += input[(i + 1) * N + (j - 1)];
            }
            if (i < N - 1 && j < N - 1) {
                sum += input[(i + 1) * N + (j + 1)];
            }
            if (input[i * N + j] == 1) {
                if (sum < 2) {
                    output[i * N + j] = 0;
                } else if (sum == 2 || sum == 3) {
                    output[i * N + j] = 1;
                } else {
                    output[i * N + j] = 0;
                }
            } else {
                if (sum == 3) {
                    output[i * N + j] = 1;
                } else {
                    output[i * N + j] = 0;
                }
            }
        }
    }
}
