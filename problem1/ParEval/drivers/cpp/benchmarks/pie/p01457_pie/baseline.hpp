#pragma once

#include <vector>
#include <utility>
#include <string>

using namespace std;
typedef long long ll;

vector<pair<ll, char>> generateInput(int q) {
    vector<pair<ll, char>> input;
    for (int i = 0; i < q; ++i) {
        input.push_back({i + 1, (i % 2 == 0) ? '(' : ')'});
    }
    return input;
}

ll baseline(int q, const vector<pair<ll, char>>& input) {
    ll ans = 0;
    for (int i = 0; i < q; ++i) {
        ll p = input[i].first;
        char c = input[i].second;
        ll n = p;
        if (c == ')') ans -= n;
        if (c == '(') ans += n;
    }
    return ans;
}