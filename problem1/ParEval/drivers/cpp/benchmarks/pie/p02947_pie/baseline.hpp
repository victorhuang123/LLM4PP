#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<string> generateInput() {
    vector<string> A(200000);
    for (int i = 0; i < 200000; ++i) {
        A[i] = to_string(i);
    }
    return A;
}

long long baseline(int n, vector<string> A) {
    map<string, int> mp;
    for (int i = 0; i < n; ++i) {
        sort(A[i].begin(), A[i].end());
        mp[A[i]]++;
    }
    long long ze = 0;
    for (auto& it : mp) {
        int cnt = it.second;
        if (cnt <= 1) continue;
        if (cnt == 2) {
            ze += 1;
            continue;
        }
        ze += 1LL * cnt * (cnt - 1) / 2;
    }
    return ze;
}