#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> baseline(int n, vector<ll>& a) {
    vector<ll> ans(n);
    ans[0] = 0;
    for (int i = 0; i < n; i++) {
        ans[0] += a[i];
        if (i % 2 == 1)
            ans[0] -= 2 * a[i];
    }

    ans[0] = ans[0] / 2;
    for (int i = 1; i < n; i++) {
        ans[i] = a[i - 1] - ans[i - 1];
    }

    for (int i = 0; i < n; i++) {
        ans[i] *= 2;
    }

    return ans;
}

vector<ll> generateInput(int n) {
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}