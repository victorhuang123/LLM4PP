#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using ii = pair<int, int>;

using iii = pair<int, ii>;

#define vt vector

#define pq priority_queue

#define pb push_back

#define pf push_front

#define mp make_pair

#define fi first

#define se second

const int MOD = 1e9 + 7;

const int INF = 2e9;

const int N = 1e5 + 5;

int baseline(int n, int m, vt<ii>& edges) {
    vt<int> v[N];
    bool vis[N] = {false};
    int ans = 0;

    for(auto& edge : edges) {
        int a = edge.fi, b = edge.se;
        v[a].pb(b);
        v[b].pb(a);
    }

    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            stack<int> st;
            st.push(i);
            vis[i] = true;
            while(!st.empty()) {
                int u = st.top();
                st.pop();
                for(int x : v[u]) {
                    if(!vis[x]) {
                        vis[x] = true;
                        st.push(x);
                    }
                }
            }
            ans++;
        }
    }

    return ans - 1;
}

vt<ii> generateInput(int n, int m) {
    vt<ii> edges;
    for(int i = 0; i < m; i++) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        edges.pb(mp(a, b));
    }
    return edges;
}