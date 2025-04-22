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

vector<int> baseline(int v, int e, vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(v);
    vector<int> articulations;
    vector<bool> used_v(v, false);
    vector<map<int, bool>> used_e(v);
    vector<int> ord(v, 0);
    vector<int> lowlink(v, 0);

    auto dfs = [&](auto self, int v, int p, int &k) -> void {
        used_v[v] = true;
        ord[v] = lowlink[v] = k++;
        
        bool is_articulation = false;
        int count = 0;
        for(int u : graph[v]){
            if(!used_v[u]){
                ++count;
                used_e[v][u] = true;
                self(self, u, v, k);
                lowlink[v] = min(lowlink[v], lowlink[u]);
                if(p != -1 && ord[v] <= lowlink[u]) is_articulation = true;
            } else if(!used_e[u][v]) lowlink[v] = min(lowlink[v], ord[u]);
        }
        
        if(p == -1 && count > 1) is_articulation = true;
        if(is_articulation) articulations.push_back(v);
    };

    rep(i, 0, e){
        int s = edges[i].first;
        int t = edges[i].second;
        graph[s].push_back(t);
        graph[t].push_back(s);
    }
    
    int k = 0;
    dfs(dfs, 0, -1, k);
    
    sort(articulations.begin(), articulations.end());
    articulations.erase(unique(articulations.begin(), articulations.end()), articulations.end());
    
    return articulations;
}

vector<pair<int, int>> generate_input(int v, int e) {
    vector<pair<int, int>> edges;
    for(int i = 0; i < e; ++i) {
        int s = rand() % v;
        int t = rand() % v;
        edges.push_back({s, t});
    }
    return edges;
}