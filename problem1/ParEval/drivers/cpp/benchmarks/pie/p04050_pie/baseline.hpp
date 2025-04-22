#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<int> baseline(int n, int m, vector<int> a) {
    int odd = 0, tot = 0;
    vector<int> oddnum(2);
    oddnum[0] = 1; oddnum[1] = m;
    for (int i = 1; i <= m; i++) {
        if (~a[i] & 1) continue;
        oddnum[odd++] = i;
        if (odd > 2) {
            return { -1 }; // Impossible case
        }
    }
    swap(a[1], a[oddnum[0]]);
    swap(a[m], a[oddnum[1]]);
    if (m == 1 && a[1] == 1) {
        return { 1, 1, 1 };
    }
    vector<int> result;
    for (int i = 1; i <= m; i++) result.push_back(a[i]);
    if (m == 1) {
        result.push_back(2);
        result.push_back(a[1] - 1);
        result.push_back(1);
        return result;
    }
    result.push_back(a[m] > 1 ? m : m - 1);
    result.push_back(a[1] + 1);
    for (int i = 2; i < m; i++) result.push_back(a[i]);
    if (a[m] > 1) result.push_back(a[m] - 1);
    return result;
}

vector<int> generateInput() {
    int n = 100, m = 100;
    vector<int> a(m + 1);
    for (int i = 1; i <= m; i++) {
        a[i] = i;
    }
    return a;
}