#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<tuple<int, int, ll>> generateInput(int N) {
    vector<tuple<int, int, ll>> edges;
    for (int i = 1; i < N; i++) {
        edges.push_back(make_tuple(i, i + 1, 1LL));
    }
    return edges;
}

ll baseline(int N, int Q, int K, vector<tuple<int, int, ll>>& edges, vector<pair<int, int>>& queries) {
    vector<vector<pair<int, ll>>> eda(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int a = get<0>(edges[i]);
        int b = get<1>(edges[i]);
        ll c = get<2>(edges[i]);
        eda[a].push_back(make_pair(b, c));
        eda[b].push_back(make_pair(a, c));
    }

    vector<ll> kyori(N + 1, 0);

    vector<pair<int, ll>> que;
    que.push_back(make_pair(K, 0));

    while (!que.empty()) {
        vector<pair<int, ll>> que2;
        for (auto itr : que) {
            if (kyori[itr.first] == 0) {
                kyori[itr.first] = itr.second;
                for (auto itr2 : eda[itr.first]) {
                    que2.push_back(make_pair(itr2.first, itr.second + itr2.second));
                }
            }
        }
        que = que2;
    }

    ll result = 0;
    for (int i = 0; i < Q; i++) {
        int X = queries[i].first;
        int Y = queries[i].second;
        result += kyori[X] + kyori[Y];
    }
    return result;
}