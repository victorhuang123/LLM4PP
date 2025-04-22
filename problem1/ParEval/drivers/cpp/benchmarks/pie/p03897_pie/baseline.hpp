#pragma once

#include<bits/stdc++.h>

using namespace std;

using Int = long long;

vector<pair<int, int>> baseline(int n) {
    vector<vector<int>> s(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if((i + j) % 2 == 0) s[i][j] = 1;

    for(int i = 0; i < n; i += 3)
        for(int j = 0; j < n; j++)
            s[i][j] = 1;

    for(int j = 0; j < n; j++)
        s[n - 1][j] = 1;

    for(int i = 0; i < n; i++)
        s[i][0] = 1;

    using P = pair<int, int>;
    vector<P> ans;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(((i + j) & 1) && s[i][j]) ans.emplace_back(i, j);

    return ans;
}