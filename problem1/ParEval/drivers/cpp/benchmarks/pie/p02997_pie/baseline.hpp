#pragma once

#include<bits/stdc++.h>

using namespace std;

#define pi acos(0.0)

#define ll long long

#define f first

#define s second

#define gap ' '

#define pb push_back

vector<pair<int, int>> baseline(int n, int k) {
    if (((n - 2) * (n - 1)) / 2 < k) {
        return {{-1, -1}};
    }

    vector<pair<int, int>> ara;
    for (int i = 2; i <= n; i++) {
        ara.pb({1, i});
    }

    vector<pair<int, int>> p;
    for (int i = 2; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            p.pb({i, j});
        }
    }

    for (int i = 0; i < ((n - 2) * (n - 1)) / 2 - k; i++) {
        ara.pb(p[i]);
    }

    return ara;
}

vector<pair<int, int>> generateInput() {
    int n = 1000;  // Large n to test efficiency
    int k = 100000;  // Large k to test efficiency
    return baseline(n, k);
}