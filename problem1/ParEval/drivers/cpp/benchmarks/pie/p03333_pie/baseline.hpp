#pragma once

#include <bits/stdc++.h>

#define all(c) c.begin(), c.end()
#define rall(c) c.rbegin(), c.rend()

using namespace std;

typedef long long ll;

ll baseline(int n, const vector<int>& l, const vector<int>& r) {
    ll ans = 0;
    vector<int> sorted_l = l;
    vector<int> sorted_r = r;
    sort(rall(sorted_l));
    sort(all(sorted_r));
    for(int i = 0; i < n; i++) {
        if(sorted_l[i] - sorted_r[i] <= 0)
            break;
        ans += sorted_l[i] - sorted_r[i];
    }
    return 2 * ans;
}

vector<int> generateInput(int n) {
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = rand() % 1000000 + 1;
    }
    return v;
}