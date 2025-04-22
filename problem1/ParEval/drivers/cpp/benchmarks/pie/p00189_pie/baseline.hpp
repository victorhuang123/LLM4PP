#pragma once

#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

int baseline(int n, const vector<vector<int>>& edges) {
    const int N = 2010;
    const int INF = 0x3f3f3f;
    vector<vector<int>> maps(N, vector<int>(N, INF));
    vector<int> dist(N);
    vector<int> vis(N);

    for (int i = 0; i < N; ++i) {
        maps[i][i] = 0;
    }

    int Max = -1;
    for (const auto& edge : edges) {
        int a = edge[0];
        int b = edge[1];
        int c = edge[2];
        maps[a][b] = maps[b][a] = min(maps[a][b], c);
        Max = max(Max, a);
        Max = max(Max, b);
    }

    int sum = INF;
    int index = 0;
    for (int i = 0; i <= Max; ++i) {
        fill(dist.begin(), dist.end(), INF);
        fill(vis.begin(), vis.end(), 0);
        dist[i] = 0;

        for (int j = 0; j <= Max; ++j) {
            int Min = INF, u = -1;
            for (int k = 0; k <= Max; ++k) {
                if (!vis[k] && dist[k] < Min) {
                    Min = dist[k];
                    u = k;
                }
            }
            if (u == -1) break;
            vis[u] = 1;
            for (int k = 0; k <= Max; ++k) {
                if (!vis[k] && dist[k] > dist[u] + maps[u][k]) {
                    dist[k] = dist[u] + maps[u][k];
                }
            }
        }

        int s = 0;
        for (int j = 0; j <= Max; ++j) {
            s += dist[j];
        }
        if (s < sum) {
            index = i;
            sum = s;
        }
    }

    return index * 1000000 + sum;
}

vector<vector<int>> generateInput() {
    const int N = 2000;
    const int M = 100000;
    vector<vector<int>> edges(M, vector<int>(3));
    for (int i = 0; i < M; ++i) {
        edges[i][0] = rand() % N;
        edges[i][1] = rand() % N;
        edges[i][2] = rand() % 1000 + 1;
    }
    return edges;
}