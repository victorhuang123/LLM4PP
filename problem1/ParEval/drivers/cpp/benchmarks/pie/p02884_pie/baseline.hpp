#pragma once

#include <vector>
#include <limits>

using namespace std;

double baseline(int N, int M, const vector<vector<int>>& edges) {
    vector<vector<int>> g(2 * 100000);
    for (const auto& edge : edges) {
        g[edge[0]].push_back(edge[1]);
    }
    vector<double> dp(N);
    dp[N - 1] = 0;
    for (int i = N - 2; i >= 0; --i) {
        double sum = 0;
        for (const auto& e : g[i]) {
            sum += dp[e];
        }
        sum /= g[i].size();
        dp[i] = sum + 1;
    }
    double res = numeric_limits<double>::max();
    for (int d = N - 2; d >= 0; --d) {
        vector<double> tdp = dp;
        double sum = 0;
        int mu = g[d][0];
        for (const auto& e : g[d]) {
            sum += dp[e];
            if (dp[mu] < dp[e]) mu = e;
        }
        sum -= dp[mu];
        if (g[d].size() == 1) continue;
        sum /= (g[d].size() - 1);
        tdp[d] = sum + 1;
        for (int i = d - 1; i >= 0; --i) {
            sum = 0;
            for (const auto& e : g[i]) {
                sum += tdp[e];
            }
            sum /= g[i].size();
            tdp[i] = sum + 1;
        }
        res = min(res, tdp[0]);
    }
    if (res > numeric_limits<double>::max() / 2) {
        res = dp[0];
    }
    return res;
}

vector<vector<int>> generateInput(int N, int M) {
    vector<vector<int>> edges(M, vector<int>(2));
    for (int i = 0; i < M; ++i) {
        edges[i][0] = rand() % N;
        edges[i][1] = rand() % N;
    }
    return edges;
}