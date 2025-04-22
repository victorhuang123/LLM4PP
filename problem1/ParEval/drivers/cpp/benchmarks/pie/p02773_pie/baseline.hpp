#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<string> generate_input(int n) {
    vector<string> input(n);
    for (int i = 0; i < n; ++i) {
        input[i] = "string_" + to_string(i % 1000);
    }
    return input;
}

vector<string> baseline(int n, const vector<string>& input) {
    map<string, int> mp;
    map<int, vector<string>> rmp;
    int mx = -1;

    for (const string& s : input) {
        mx = max(mx, ++mp[s]);
        rmp[mp[s]].push_back(s);
    }

    sort(rmp[mx].begin(), rmp[mx].end());
    return rmp[mx];
}