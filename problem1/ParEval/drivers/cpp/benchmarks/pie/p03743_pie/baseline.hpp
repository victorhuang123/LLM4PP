#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<string> baseline(int n, int m, vector<int>& a, int q, vector<int>& queries) {
    vector<int> c(n + 1), f(n + 2);
    vector<string> result;
    int d = m;

    for (int i = 1; i <= n; i++) {
        if (abs(d - a[i - 1]) < d) d = abs(d - a[i - 1]);
        c[i] = d;
    }

    f[n + 1] = 1;
    for (int i = n; i >= 1; i--) {
        f[i] = f[i + 1];
        if (abs(f[i] - a[i - 1]) < f[i]) f[i] = f[i] + a[i - 1];
    }

    c[0] = m;
    for (int i = 0; i < q; i++) {
        int x = queries[i];
        if (c[x - 1] >= f[x + 1]) result.push_back("YES");
        else result.push_back("NO");
    }

    return result;
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}