#pragma once

#include <vector>
#include <array>
#include <algorithm>

using lli = long long int;

constexpr lli inf = 1e18 + 114514;
constexpr int MAX_N = 1e3;
constexpr int MAX_H = 1e4;

lli baseline(int H, int n, const std::vector<std::pair<int, int>>& spells) {
    std::array<std::array<lli, MAX_H + 1>, MAX_N + 1> DP;
    for(int i = 0; i <= n; ++i) for(int j = 0; j <= H; ++j) DP[i][j] = inf;
    DP[0][H] = 0;

    for(int i = 0; i < n; ++i){
        int a = spells[i].first, b = spells[i].second;
        for(int j = 0; j <= H; ++j){
            int nj = j - a; if(nj < 0) nj = 0;
            DP[i+1][nj] = std::min(DP[i+1][nj], DP[i][j] + b);
            DP[i+1][j] = std::min(DP[i+1][j], DP[i][j]);
        }
        for(int j = H; j >= 0; --j){
            int nj = j - a; if(nj < 0) nj = 0;
            DP[i+1][nj] = std::min(DP[i+1][nj], DP[i+1][j] + b);
        }
    }
    return DP[n][0];
}

std::vector<std::pair<int, int>> generateInput(int H, int n) {
    return std::vector<std::pair<int, int>>(n, {10, 1});
}