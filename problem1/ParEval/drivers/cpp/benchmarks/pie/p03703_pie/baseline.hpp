#pragma once

#include <vector>
#include <algorithm>

using namespace std;

long long baseline(int n, int k, vector<int>& a) {
    vector<long long> sum(n + 1, 0);
    vector<long long> t(n + 1, 0);
    vector<long long> tree(n + 10, 0);

    for (int i = 1; i <= n; i++) {
        t[i] = sum[i] = sum[i - 1] + a[i - 1] - k;
    }

    sort(t.begin(), t.begin() + n + 1);
    auto last = unique(t.begin(), t.begin() + n + 1);
    int m = last - t.begin();

    for (int i = 0; i <= n; i++) {
        sum[i] = lower_bound(t.begin(), t.begin() + m, sum[i]) - t.begin() + 1;
    }

    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        int x = sum[i];
        while (x <= n + 10) {
            tree[x]++;
            x += x & -x;
        }
        x = sum[i];
        while (x) {
            ans += tree[x];
            x -= x & -x;
        }
    }

    return ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}