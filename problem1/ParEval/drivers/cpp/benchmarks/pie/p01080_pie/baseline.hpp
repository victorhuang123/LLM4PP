#pragma once

#include <vector>
#include <algorithm>

using namespace std;

#define rep(i,a,n) for(int (i)=(a); (i)<(n); (i)++)
#define repq(i,a,n) for(int (i)=(a); (i)<=(n); (i)++)
#define repr(i,a,n) for(int (i)=(a); (i)>=(n); (i)--)
#define all(v) begin(v), end(v)
#define pb(a) push_back(a)
#define fr first
#define sc second
#define INF 2000000000
#define int long long int

typedef vector<int> VI;
typedef pair<int, int> pii;

vector<int> baseline(int n, vector<pair<int, int>>& edges) {
    vector<int> step(n, 0), ans(n, 0);
    vector<vector<int>> G(n);

    rep(i,0,n-1) {
        int u = edges[i].first, v = edges[i].second;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    function<void(int, int)> dfs = [&](int idx, int par) {
        for(auto to : G[idx]) {
            if(to == par) continue;
            dfs(to, idx);
            step[idx] = max(step[idx], step[to] + 1);
        }
    };

    function<void(int, int, int)> dfs2 = [&](int idx, int d_par, int par) {
        vector<pii> rec;
        rec.push_back(pii(0, -1));
        for(auto to : G[idx]) {
            if(to == par) rec.push_back(pii(d_par + 1, to));
            else rec.push_back(pii(step[to] + 1, to));
        }
        sort(rec.rbegin(), rec.rend());
        ans[idx] = rec[0].first;
        for(auto to : G[idx]) {
            if(to == par) continue;
            dfs2(to, rec[ rec[0].second == to ].first, idx);
        }
    };

    dfs(0, -1);
    dfs2(0, 0, -1);

    vector<int> result(n);
    rep(i,0,n) result[i] = (n-1) * 2 - ans[i];
    return result;
}

vector<pair<int, int>> generate_input(int n) {
    vector<pair<int, int>> edges;
    rep(i,1,n) {
        edges.push_back({i, i+1});
    }
    return edges;
}