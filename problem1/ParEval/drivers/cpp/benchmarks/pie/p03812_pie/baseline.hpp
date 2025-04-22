#pragma once

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair<long long, long long> ii;

vector<long long> baseline(long long n, vector<long long>& a, vector<ii>& edges) {
    vector<ii> vec;
    vector<long long> dp(n + 1, 0);
    vector<vector<int>> graph(n + 1);

    for(int i = 1; i <= n; i++){
        vec.pb(mp(a[i], i));
    }

    for(int i = 0; i < edges.size(); i++){
        int u = edges[i].fi;
        int v = edges[i].se;
        graph[u].pb(v);
        graph[v].pb(u);
    }

    sort(vec.begin(), vec.end());

    for(int i = 0; i < vec.size(); i++){
        if(dp[vec[i].se] == 0){
            for(int j = 0; j < graph[vec[i].se].size(); j++){
                int v = graph[vec[i].se][j];
                if(a[v] > a[vec[i].se])
                    dp[v] = 1;
            }
        }
    }

    vector<long long> result;
    for(int i = 1; i <= n; i++){
        if(dp[i])
            result.pb(i);
    }

    return result;
}

vector<long long> generateInput(long long n) {
    vector<long long> a(n + 1);
    vector<ii> edges;
    for(long long i = 1; i <= n; i++) {
        a[i] = rand() % 1000000 + 1;
    }
    for(long long i = 1; i <= n; i++) {
        for(long long j = i + 1; j <= min(i + 10, n); j++) {
            edges.pb(mp(i, j));
        }
    }
    return a;
}