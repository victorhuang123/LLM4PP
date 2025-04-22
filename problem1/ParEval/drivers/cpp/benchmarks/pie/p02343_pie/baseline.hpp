#pragma once

#include <vector>
#include <utility>

using namespace std;

vector<int> baseline(int n, int q, vector<pair<int, pair<int, int>>>& queries){
    vector<int> result;
    vector<int> s(n);
    vector<vector<int>> l(n);

    for(int i = 0; i < n; i++){
        s[i] = i;
        l[i].push_back(i);
    }

    for(int i = 0; i < q; i++){
        int com = queries[i].first;
        int x = queries[i].second.first;
        int y = queries[i].second.second;

        if(com == 0){
            if(s[x] == s[y]) continue;

            int sx = s[x];
            int sy = s[y];
            for(int j = 0; j < l[sy].size(); j++){
                int tmp = l[sy][j];
                s[tmp] = sx;
                l[sx].push_back(tmp);
            }
            l[sy].clear();
        } else {
            result.push_back(s[x] == s[y] ? 1 : 0);
        }
    }

    return result;
}

vector<pair<int, pair<int, int>>> generateInput(int n, int q){
    vector<pair<int, pair<int, int>>> queries;
    for(int i = 0; i < q; i++){
        int type = rand() % 2;
        int x = rand() % n;
        int y = rand() % n;
        queries.push_back({type, {x, y}});
    }
    return queries;
}