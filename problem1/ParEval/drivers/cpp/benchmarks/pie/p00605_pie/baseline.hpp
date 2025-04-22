#pragma once

#include <vector>

using namespace std;

vector<int> generateInput(int n, int k) {
    vector<int> initialS(k, 1000000);
    vector<vector<int>> B(n, vector<int>(k, 1000));
    return initialS;
}

bool baseline(int n, int k, const vector<int>& initialS, const vector<vector<int>>& B) {
    vector<int> S = initialS;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            S[j] -= B[i][j];
        }
    }

    for (int i = 0; i < k; i++) {
        if (S[i] < 0) {
            return false;
        }
    }

    return true;
}