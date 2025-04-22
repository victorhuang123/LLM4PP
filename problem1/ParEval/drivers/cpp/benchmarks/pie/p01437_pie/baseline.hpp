#pragma once

#include <vector>
#include <cstring>
#include <algorithm>
#define N 110
#define M 100100
using namespace std;

const int dx[5] = {-1, 0, 1, 0};
const int dy[5] = {0, 1, 0, -1};
const char fa[5] = {'N', 'E', 'S', 'W'};

long long dp[N][N][5];
int ansx, ansy, ansf;

void dfs1(int x, int y, int f, long long l, long long ll, int map[N][N]) {
    int tof = f;
    while (l < ll) {
        while (map[x + dx[tof]][y + dy[tof]] == 0)
            tof = (tof + 1) % 4;
        x += dx[tof]; y += dy[tof];
        l++;
        if (dp[x][y][tof] != -1) {
            long long loo = l - dp[x][y][tof];
            long long rest = ll - l;
            long long div = rest / loo;
            l += div * loo;
            memset(dp, -1, sizeof dp);
        } else {
            dp[x][y][tof] = l;
        }
    }
    ansx = x; ansy = y; ansf = tof;
}

int baseline(int h, int w, long long ll, int sx, int sy, int sf, int map[N][N]) {
    memset(dp, -1, sizeof dp);
    dp[sx][sy][sf] = 0;
    dfs1(sx, sy, sf, 0, ll, map);
    return ansx * 10000 + ansy * 10 + ansf;
}

vector<vector<int>> generateInput() {
    vector<vector<int>> map(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == 0 || i == N - 1 || j == 0 || j == N - 1) {
                map[i][j] = 1;
            }
        }
    }
    return map;
}