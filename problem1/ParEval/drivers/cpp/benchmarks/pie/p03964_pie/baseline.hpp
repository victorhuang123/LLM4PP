#pragma once

#include<bits/stdc++.h>

#define ll long long

using namespace std;

const ll inf=1e18;

ll baseline(int n, const vector<ll>& t, const vector<ll>& a) {
    ll ans1 = t[1], ans2 = a[1];
    for(int i = 2; i <= n; i++) {
        if(ans1 * a[i] == ans2 * t[i]) continue;
        else {
            ll l = 1, r = inf / max(a[i], t[i]) + 1;
            ll ans = r;
            while(l <= r) {
                ll mid = (l + r) >> 1;
                if(mid * t[i] >= ans1 && mid * a[i] >= ans2) {
                    ans = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            ans1 = ans * t[i];
            ans2 = ans * a[i];
        }
    }
    return ans1 + ans2;
}

vector<pair<ll, ll>> generateInput(int n) {
    vector<pair<ll, ll>> input(n + 1);
    for(int i = 1; i <= n; i++) {
        input[i].first = rand() % 1000000 + 1;
        input[i].second = rand() % 1000000 + 1;
    }
    return input;
}