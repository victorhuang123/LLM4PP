#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int n, int m, const vector<int>& k) {
    vector<int> kk((n + 1) * (n + 1), k_copy = k;
    k_copy.insert(k_copy.begin(), 0);

    for (int c = 0; c <= n; ++c) {
        for (int d = 0; d <= n; ++d) {
            kk[c * (n + 1) + d] = k_copy[c] + k_copy[d];
        }
    }

    sort(kk.begin(), kk.end());
    int ans = 0;

    for (int a = 0; a <= n; ++a) {
        for (int b = 0; b <= n; ++b) {
            int target = m - k_copy[a] - k_copy[b];
            auto it = upper_bound(kk.begin(), kk.end(), target);
            if (it != kk.begin()) {
                --it;
                int tmp = *it + k_copy[a] + k_copy[b];
                if (tmp <= m) ans = max(ans, tmp);
            }
            if (it != kk.end()) {
                int tmp = *it + k_copy[a] + k_copy[b];
                if (tmp <= m) ans = max(ans, tmp);
            }
        }
    }

    return ans;
}

vector<int> generateInput(int n) {
    vector<int> k(n + 1);
    for (int i = 1; i <= n; ++i) {
        k[i] = i * 1000;
    }
    return k;
}