#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int N, const vector<int>& input) {
    int r{2};
    vector<int> A(N + 1);

    while (r--)
        for (int i = 1; i <= N; ++i) A[i] = input[i - 1] + max(A[i - 1], A[i]);

    return A[N];
}

vector<int> generateInput(int N) {
    vector<int> input(N);
    for (int i = 0; i < N; ++i) {
        input[i] = i + 1; // Example input, can be adjusted for different test cases
    }
    return input;
}