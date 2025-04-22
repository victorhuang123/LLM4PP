#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int width, int height, vector<vector<char>> grid, int targetX, int targetY, vector<pair<int, int>> operations) {
    int N = 1000021;
    vector<int> par(N), Rank(N);
    for (int i = 0; i < N; i++) par[i] = i, Rank[i] = 0;

    auto find = [&](int x) {
        while (par[x] != x) {
            par[x] = par[par[x]];
            x = par[x];
        }
        return x;
    };

    auto unite = [&](int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (Rank[x] < Rank[y]) par[x] = y;
        else par[y] = x, Rank[x] += (Rank[x] == Rank[y]);
    };

    auto same = [&](int x, int y) { return find(x) == find(y); };

    auto Pos = [&](int x, int y) { return width * y + x; };

    int dx[] = {0, 0, -1, 1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            for (int k = 0; k < 4; k++) {
                int ni = i + dy[k], nj = j + dx[k];
                if (grid[i][j] == '#') continue;
                if (ni < 0 || nj < 0 || ni >= height || nj >= width || grid[ni][nj] == '#') continue;
                unite(Pos(j, i), Pos(nj, ni));
            }

    int t = Pos(targetX, targetY);
    int ans = -1;
    if (same(0, t)) ans = 0;

    for (int i = 0; i < operations.size(); i++) {
        int a = operations[i].first, b = operations[i].second;
        for (int k = 0; k < 4; k++) {
            int ny = b + dy[k], nx = a + dx[k];
            if (ny < 0 || nx < 0 || ny >= height || nx >= width || grid[ny][nx] == '#') continue;
            unite(Pos(a, b), Pos(nx, ny));
        }
        grid[b][a] = '.';
        if (same(0, t)) {
            ans = i + 1;
            break;
        }
    }

    return ans;
}

vector<vector<char>> generateInput(int width, int height) {
    vector<vector<char>> grid(height, vector<char>(width, '.'));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rand() % 10 == 0) grid[i][j] = '#';
        }
    }
    return grid;
}