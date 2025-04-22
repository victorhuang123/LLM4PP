#pragma once

#include <vector>
#include <deque>

using namespace std;

long long baseline(int n, long long C, vector<long long>& heights) {
    vector<long long> h(n + 2);
    vector<long long> dp(n + 2);

    for (int i = 1; i <= n; i++) {
        h[i] = heights[i - 1];
    }
    h[n + 1] = h[n] + 1;

    dp[1] = 0;
    deque<int> Q = {1};
    for (int i = 2; i <= n; i++) {
        while (Q.size() > 1 && (dp[Q[1]] + (h[i] - h[Q[1]]) * (h[i] - h[Q[1]]) < dp[Q[0]] + (h[i] - h[Q[0]]) * (h[i] - h[Q[0]])) {
            Q.pop_front();
        }

        dp[i] = dp[Q[0]] + (h[i] - h[Q[0]]) * (h[i] - h[Q[0]]) + C;

        while (Q.size() > 1 && (h[Q[Q.size() - 2]] * h[Q[Q.size() - 2]] + dp[Q[Q.size() - 2]] - h[i] * h[i] - dp[i]) / (2 * h[Q[Q.size() - 2]] - 2 * h[i]) <= (h[Q[Q.size() - 2]] * h[Q[Q.size() - 2]] + dp[Q[Q.size() - 2]] - h[Q.back()] * h[Q.back()] - dp[Q.back()]) / (2 * h[Q[Q.size() - 2]] - 2 * h[Q.back()])) {
            Q.pop_back();
        }
        Q.push_back(i);
    }

    return dp[n];
}

vector<long long> generateInput(int n) {
    vector<long long> heights(n);
    for (int i = 0; i < n; i++) {
        heights[i] = i + 1;
    }
    return heights;
}