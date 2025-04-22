#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(const vector<int>& A, const vector<int>& B) {
    int n = A.size();
    vector<int> V(n);
    for (int i = 0; i < n; i++) {
        V[i] = A[i] - B[i];
    }
    
    vector<int> HOST(n, 0);
    HOST[0] = max(V[0], 0);
    for (int i = 1; i < n; i++) {
        HOST[i] = max(V[i] + HOST[i-1], HOST[i-1]);
    }
    return HOST[n-1];
}

vector<int> generateInput(int size) {
    vector<int> A(size);
    vector<int> B(size);
    for (int i = 0; i < size; i++) {
        A[i] = size - i;
        B[i] = i + 1;
    }
    return {A, B};
}