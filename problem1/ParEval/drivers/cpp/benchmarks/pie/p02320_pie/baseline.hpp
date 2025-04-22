#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int N, int W, vector<int>& values, vector<int>& weights, vector<int>& counts) {
    vector<int> dp(W + 1, -1);
    dp[0] = 0;

    for (int i = 0; i < N; i++) {
        int v = values[i];
        int w = weights[i];
        int m = counts[i];
        for (int k = 0; m > 0; k++) {
            int key = min(m, (1 << k));
            m -= key;
            for (int j = W; j >= key * w; j--) {
                if (dp[j - key * w] != -1) {
                    dp[j] = max(dp[j], dp[j - key * w] + key * v);
                }
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}

vector<int> generateExampleInput(int N, int W) {
    vector<int> values(N);
    vector<int> weights(N);
    vector<int> counts(N);

    for (int i = 0; i < N; i++) {
        values[i] = (i + 1) * 100;
        weights[i] = (i + 1) * 10;
        counts[i] = (i + 1) * 5;
    }

    return {values, weights, counts};
}