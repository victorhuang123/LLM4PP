#pragma once

#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct node {
    int x;
    int y;
    int deep;
    int n;
};

int baseline(int h, int w, int n, const vector<vector<char>>& map) {
    bool vis[10][h + 2][w + 2];
    memset(vis, false, sizeof(vis));

    int sx = -1, sy = -1;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (map[i][j] == 'S') {
                sx = i;
                sy = j;
                break;
            }
        }
        if (sx != -1) break;
    }

    node t;
    t.x = sx;
    t.y = sy;
    t.deep = 0;
    t.n = 0;
    queue<node> q;
    vis[0][sx][sy] = true;
    q.push(t);

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    int ans = -1;
    while (!q.empty()) {
        node cur = q.front();
        if (cur.n == n) {
            ans = cur.deep;
            break;
        }
        q.pop();
        for (int i = 0; i < 4; i++) {
            int tx = cur.x + dx[i];
            int ty = cur.y + dy[i];
            if (map[tx][ty] != 'X' && !vis[cur.n][tx][ty]) {
                node t = cur;
                t.x = tx;
                t.y = ty;
                t.deep++;
                if (map[tx][ty] == '1' + t.n) {
                    t.n++;
                }
                vis[t.n][tx][ty] = true;
                q.push(t);
            }
        }
    }
    return ans;
}

vector<vector<char>> generateInput(int h, int w, int n) {
    vector<vector<char>> map(h + 2, vector<char>(w + 2, 'X'));
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (i == 1 && j == 1) {
                map[i][j] = 'S';
            } else if (i == h && j == w) {
                map[i][j] = '0' + n;
            } else {
                map[i][j] = '.';
            }
        }
    }
    return map;
}