#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> generateInput(int n) {
    vector<ll> input(n);
    for (int i = 0; i < n; i++) {
        input[i] = 1e18; // Maximize the problem scale
    }
    return input;
}

ll baseline(int n, int m, vector<ll>& input) {
    priority_queue<ll> nums;
    for(int i = 0; i < n; i++) {
        nums.push(input[i]);
    }
    while(m--) {
        ll tmp = nums.top();
        nums.pop();
        nums.push(tmp / 2);
    }
    ll ans = 0;
    while(!nums.empty()) {
        ans += nums.top();
        nums.pop();
    }
    return ans;
}