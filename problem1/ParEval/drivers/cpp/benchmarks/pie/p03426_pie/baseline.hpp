#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> generateInput(int h, int w, int d) {
    vector<vector<int>> grid(h, vector<int>(w));
    int val = 1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            grid[i][j] = val++;
        }
    }
    return grid;
}

vector<pair<int, int>> generateQueries(int numQueries, int h, int w) {
    vector<pair<int, int>> queries(numQueries);
    for (int i = 0; i < numQueries; i++) {
        queries[i] = {rand() % (h * w) + 1, rand() % (h * w) + 1};
    }
    return queries;
}

vector<int> baseline(int h, int w, int d, vector<vector<int>>& grid, vector<pair<int, int>>& queries) {
    map<int, pair<int, int>> adr;
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            adr[grid[i-1][j-1]] = {i, j};
        }
    }

    vector<int> f(h * w + 1);
    for(int i = 1; i <= h * w; i++) {
        if(i <= d) {
            f[i] = 0;
        } else {
            f[i] = f[i - d] + abs(adr[i].first - adr[i - d].first) + abs(adr[i].second - adr[i - d].second);
        }
    }

    vector<int> ans;
    for(auto& query : queries) {
        int z = query.first;
        int y = query.second;
        ans.push_back(f[y] - f[z]);
    }

    return ans;
}