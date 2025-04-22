#pragma once

#include <vector>
#include <string>
#include <algorithm>

using ll = long long;

ll baseline(ll n) {
    ll ans = 0;
    std::string s, t;
    s = std::to_string(n);
    t = s;
    bool flag = true;
    for (int i = 0; i < s.size()-1; i++) {
        if (flag) {
            if (s[i + 1] - '0' != 9) {
                int a = s[i] - '0' - 1;
                s[i] = a + '0';
                s[i + 1] = '9';
            }
            else s[i + 1] = '9';
        }
        else s[i + 1] = '9';
        if (s < t) flag = false;
    }
    for (int i = 0; i < s.size(); i++) {
        ans += s[i] - '0';
    }
    return ans;
}

std::vector<ll> generateInput() {
    std::vector<ll> inputs;
    for (ll i = 0; i < 100000; ++i) {
        inputs.push_back(999999999999999999LL - i);
    }
    return inputs;
}