#pragma once

#include<vector>
#include<queue>
#include<set>
#include<cstring>

using namespace std;

typedef pair<int,int> pp;

long long baseline(int n, int m, int s, int t, vector<pair<int, int>>& edges) {
    set<int> G[105000];
    int dis[105000];
    int S[105000];

    s--, t--;
    memset(dis, 0x20, sizeof(dis));

    for(int i=0; i<m; i++) {
        int x = edges[i].first, y = edges[i].second;
        x--, y--;
        G[x].insert(y);
        G[y].insert(x);
    }

    {
        priority_queue<pp> q;
        q.push(pp(-0, s));

        while(!q.empty()) {
            pp t = q.top(); q.pop();
            int d = -t.fst, x = t.snd;

            if(dis[x] != 0x20202020) continue;
            dis[x] = d;
            S[d]++;

            for(int y : G[x])
                if(dis[y] == 0x20202020)
                    q.push(pp(-(d+1), y));
        }
    }

    int old = dis[t];
    memset(dis, 0x20, sizeof(dis));

    long long int res=0;
    {
        priority_queue<pp> q;
        q.push(pp(-0, t));

        while(!q.empty()) {
            pp t = q.top(); q.pop();
            int d = -t.fst, x = t.snd;

            if(dis[x] != 0x20202020) continue;
            dis[x] = d;

            if(old-2-d >= 0)
                res += S[old-2-d];

            for(int y : G[x])
                if(dis[y] == 0x20202020)
                    q.push(pp(-(d+1), y));
        }
    }

    return res;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for(int i = 0; i < m; i++) {
        edges.push_back({rand() % n + 1, rand() % n + 1});
    }
    return edges;
}