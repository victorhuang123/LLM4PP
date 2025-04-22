#pragma once

#include <bits/stdc++.h>

using namespace std;

#define rep(i,x,y) for(int i=(x);i<(y);++i)
#define mp(a,b) make_pair((a),(b))
#define debug(x) #x << "=" << (x)

#ifdef DEBUG
#define _GLIBCXX_DEBUG
#define dump(x) std::cerr << debug(x) << " (L:" << __LINE__ << ")" << std::endl
#else
#define dump(x)
#endif

typedef long long int ll;
typedef pair<int,int> pii;

const int INF=1<<30;
const long long int INFLL=1LL<<58;
const double EPS=1e-9;
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

template <typename T> ostream &operator<<(ostream &os, const vector<T> &vec){
	os << "[";
	for (const auto &v : vec) {
		os << v << ",";
	}
	os << "]";
	return os;
}

vector<pii> baseline(int v, int e, vector<pii>& edges) {
    vector<vector<int>> graph(v);
    vector<bool> used_v(v, false);
    vector<map<int,bool>> used_e(v);
    vector<int> ord(v, -1), lowlink(v, -1);
    vector<pii> bridges;

    auto dfs = [&](auto self, int v, int &k) -> void {
        used_v[v] = true;
        ord[v] = lowlink[v] = k++;
        for(int u : graph[v]) {
            if(!used_v[u]) {
                used_e[v][u] = true;
                self(self, u, k);
                lowlink[v] = min(lowlink[v], lowlink[u]);
                if(ord[v] < lowlink[u]) bridges.push_back(make_pair(min(v,u), max(v,u)));
            } else if(!used_e[u][v]) lowlink[v] = min(lowlink[v], ord[u]);
        }
    };

    rep(i,0,e) {
        int s = edges[i].first;
        int t = edges[i].second;
        graph[s].push_back(t);
        graph[t].push_back(s);
    }

    int k = 0;
    dfs(dfs, 0, k);

    sort(bridges.begin(), bridges.end());
    return bridges;
}

vector<pii> generate_input(int v, int e) {
    vector<pii> edges;
    rep(i, 0, e) {
        int s = rand() % v;
        int t = rand() % v;
        edges.push_back(make_pair(s, t));
    }
    return edges;
}