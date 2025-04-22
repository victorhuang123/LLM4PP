#pragma once

#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int baseline(int n, int m, vector<int>& a) {
    int lc1 = 1;
    for (int i = 0; i < n; ++i) {
        int ai = a[i] / 2;
        lc1 = lcm(lc1, ai);
        if (lc1 > m) { return 0; }
        a[i] = ai;
    }
    for (int i = 0; i < n; ++i) {
        if ((lc1 / a[i]) % 2 == 0) { return 0; }
    }
    int ans = m / lc1;
    ans = (ans + 1) / 2;
    return ans;
}

vector<int> generateInput(int n, int m) {
    vector<int> a(n, m);
    return a;
}