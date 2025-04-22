#pragma once

#include<vector>
#include<algorithm>
#include<string>

using namespace std;

const int INF = 1 << 29;

string baseline(int n, const vector<int>& c, int T) {
    if (c[0] != 1) {
        return "Cannot pay some amount";
    }

    const int L = 100 * c[n - 1];
    vector<int> dp1(L, INF), dp2(L, INF);

    dp1[0] = 0;
    for (int k = 0; k < n; ++k) {
        for (int p = c[k]; p < L; ++p) {
            dp1[p] = min(dp1[p], dp1[p - c[k]] + 1);
        }
    }

    dp2[0] = 0;
    for (int p = 1; p < L; ++p) {
        for (int k = n - 1; k >= 0; --k) {
            if (p - c[k] >= 0) {
                dp2[p] = dp2[p - c[k]] + 1;
                break;
            }
        }
    }

    for (int i = 0; i < L; ++i) {
        if (dp1[i] < dp2[i]) {
            return "Cannot use greedy algorithm";
        }
    }
    return "OK";
}

vector<int> generateInput(int n) {
    vector<int> c(n);
    c[0] = 1;
    for (int i = 1; i < n; ++i) {
        c[i] = c[i - 1] * 2;
    }
    return c;
}