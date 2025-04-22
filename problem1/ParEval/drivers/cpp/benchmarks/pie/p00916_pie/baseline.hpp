#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

#define N 207

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int vis[N][N];

bool OK(int nx, int ny) {
    if (nx >= 0 && nx <= 201 && ny >= 0 && ny <= 201 && !vis[nx][ny])
        return 1;
    return 0;
}

void dfs(int x, int y) {
    vis[x][y] = 1;
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (OK(nx, ny))
            dfs(nx, ny);
    }
}

int baseline(int n, const vector<int>& l, const vector<int>& t, const vector<int>& r, const vector<int>& b) {
    vector<int> vx, vy;
    map<int, int> hx, hy;

    for (int i = 0; i < n; i++) {
        vx.push_back(l[i]);
        vx.push_back(r[i]);
        vy.push_back(t[i]);
        vy.push_back(b[i]);
    }
    sort(vx.begin(), vx.end());
    vx.erase(unique(vx.begin(), vx.end()), vx.end());
    sort(vy.begin(), vy.end());
    vy.erase(unique(vy.begin(), vy.end()), vy.end());
    for (int i = 0; i < vx.size(); i++)
        hx[vx[i]] = 2 * i + 1;
    for (int i = 0; i < vy.size(); i++)
        hy[vy[i]] = 2 * i + 1;

    vector<int> l_new(n), t_new(n), r_new(n), b_new(n);
    for (int i = 0; i < n; i++) {
        l_new[i] = hx[l[i]];
        t_new[i] = hy[t[i]];
        r_new[i] = hx[r[i]];
        b_new[i] = hy[b[i]];
    }

    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        for (int j = b_new[i]; j <= t_new[i]; j++) {
            vis[j][l_new[i]] = 1;
            vis[j][r_new[i]] = 1;
        }
        for (int j = l_new[i]; j <= r_new[i]; j++) {
            vis[t_new[i]][j] = 1;
            vis[b_new[i]][j] = 1;
        }
    }

    int cnt = 0;
    for (int i = 0; i <= 201; i++) {
        for (int j = 0; j <= 201; j++) {
            if (!vis[i][j]) {
                cnt++;
                dfs(i, j);
            }
        }
    }
    return cnt;
}

vector<vector<int>> generate_input(int n) {
    vector<int> l(n), t(n), r(n), b(n);
    for (int i = 0; i < n; i++) {
        l[i] = rand() % 100;
        t[i] = rand() % 100 + 100;
        r[i] = l[i] + rand() % 50 + 1;
        b[i] = t[i] - rand() % 50 - 1;
    }
    return {l, t, r, b};
}