#pragma once

#include <vector>

using namespace std;

typedef long long ll;

int baseline(ll aim) {
    vector<ll> a(1e5 + 7, 0);
    int ans = 0;
    for(int i = 1; i < a.size(); i++) a[i] = a[i-1] + i;
    while(a[ans] < aim) ans++;
    return ans;
}

ll generateInput() {
    return 1e18;
}