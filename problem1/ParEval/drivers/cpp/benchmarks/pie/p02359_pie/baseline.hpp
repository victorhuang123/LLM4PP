#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int n, int t, vector<int>& l, vector<int>& r) {
    vector<int> imos(t + 2, 0);

    for (int i = 0; i < n; i++) {
        imos[l[i]]++;
        imos[r[i]]--;
    }

    for (int i = 1; i <= t; i++) {
        imos[i] += imos[i - 1];
    }

    int maxi = *max_element(imos.begin(), imos.end());
    return maxi;
}

vector<int> generateInput(int n, int t) {
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        l[i] = rand() % t;
        r[i] = l[i] + rand() % (t - l[i]);
    }
    return {l, r};
}