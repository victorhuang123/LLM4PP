#pragma once

#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int baseline(int N, vector<pair<int, int>>& A) {
    for (int i = 0; i < N; i++) {
        A[i].second = i;
    }
    sort(A.begin(), A.end());
    int result = 0;
    for(int i = 0; i < N; i++)
        if(abs(A[i].second - i) % 2 != 0)
            result++;
    return result / 2;
}

vector<pair<int, int>> generateInput(int N) {
    vector<pair<int, int>> A(N);
    for (int i = 0; i < N; i++) {
        A[i].first = N - i; // Example input to maximize problem scale
    }
    return A;
}