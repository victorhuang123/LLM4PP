#pragma once

#include<vector>
#include<queue>

using namespace std;

int baseline(int n, vector<int>& edges) {
    vector<vector<int>> v(n);
    vector<int> dp(n, 0), deg(n, 0);
    int res = 0, t;
    int mx = 0;
    queue<int> q;

    for(int i = 0; i < edges.size(); i += 2) {
        int x = edges[i], y = edges[i+1];
        v[x].push_back(y);
        v[y].push_back(x);
        deg[x]++;
        deg[y]++;
    }

    for(int i = 0; i < n; i++) {
        if(v[i].size() > mx)
            mx = v[i].size();
    }

    if(mx <= 2) {
        return 1;
    }

    for(int i = 0; i < n; i++) {
        if(deg[i] == 1) q.push(i);
    }

    while(!q.empty()) {
        int p = q.front(), to = -1; q.pop();
        for(int i = 0; i < v[p].size(); i++) {
            to = v[p][i];
            if(deg[to] != 1) break;
        }
        if(deg[to] == 2) {
            deg[to] = 1;
            q.push(to);
        }
    }

    for(int i = 0; i < n; i++) {
        if(deg[i] == 1) continue;
        t = 0;
        for(int j = 0; j < v[i].size(); j++) {
            int to = v[i][j];
            if(deg[to] == 1) t++;
        }
        res += max(0, t - 1);
    }

    return res;
}

vector<int> generateInput(int n) {
    vector<int> edges;
    for(int i = 0; i < n; i++) {
        edges.push_back(i);
        edges.push_back((i + 1) % n);
    }
    return edges;
}