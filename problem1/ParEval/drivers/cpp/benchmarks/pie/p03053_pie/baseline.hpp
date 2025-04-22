#pragma once

#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
};

int baseline(int h, int w, const vector<string>& grid) {
    queue<Node> Q;
    vector<vector<int>> a(h + 2, vector<int>(w + 2, 0));
    vector<vector<int>> d(h + 2, vector<int>(w + 2, 0));
    vector<vector<int>> vis(h + 2, vector<int>(w + 2, 0));

    for (int i = 1; i <= h; i++) {
        string s = grid[i - 1];
        for (int j = 0; j < w; j++) {
            if (s[j] == '#') {
                a[i][j + 1] = 1;
                Q.push({i, j + 1});
                vis[i][j + 1] = 1;
            } else {
                a[i][j + 1] = 0;
            }
        }
    }

    while (!Q.empty()) {
        Node p = Q.front();
        Q.pop();

        if (p.x > 1 && !vis[p.x - 1][p.y]) {
            d[p.x - 1][p.y] = d[p.x][p.y] + 1;
            Q.push({p.x - 1, p.y});
            vis[p.x - 1][p.y] = 1;
        }
        if (p.y > 1 && !vis[p.x][p.y - 1]) {
            d[p.x][p.y - 1] = d[p.x][p.y] + 1;
            Q.push({p.x, p.y - 1});
            vis[p.x][p.y - 1] = 1;
        }
        if (p.x < h && !vis[p.x + 1][p.y]) {
            d[p.x + 1][p.y] = d[p.x][p.y] + 1;
            Q.push({p.x + 1, p.y});
            vis[p.x + 1][p.y] = 1;
        }
        if (p.y < w && !vis[p.x][p.y + 1]) {
            d[p.x][p.y + 1] = d[p.x][p.y] + 1;
            Q.push({p.x, p.y + 1});
            vis[p.x][p.y + 1] = 1;
        }
    }

    int ans = 0;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            ans = max(ans, d[i][j]);
        }
    }

    return ans;
}

vector<string> generateInput(int h, int w) {
    vector<string> grid(h, string(w, '.'));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i == 0 || j == 0 || i == h - 1 || j == w - 1) {
                grid[i][j] = '#';
            }
        }
    }
    return grid;
}