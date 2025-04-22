#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;
using ll = long long;

ll baseline(int N, string S) {
    ll mod = 998244353;
    vector<ll> fact(101010);
    fact[0] = 1;
    for (ll i = 1; i < 101010; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= mod;
    }

    ll ans = fact[N];
    map<char, int> mp;
    mp['R'] = 0;
    mp['G'] = 0;
    mp['B'] = 0;
    for (int i = 0; i < 3 * N; i++) {
        char c = S[i];
        vector<pair<int, char>> v;
        for (auto &x : mp) v.push_back({x.second, x.first});
        sort(v.begin(), v.end());
        if (mp[c] == v[0].first) {
            if (v[0].first < v[1].first) ans *= v[1].first - v[0].first;
            else if (v[1].first < v[2].first) ans *= v[2].first - v[0].first;
        }
        else if (mp[c] == v[1].first) {
            if (v[1].first < v[2].first) ans *= v[2].first - v[1].first;
        }
        mp[c]++;
        ans %= mod;
    }
    return ans;
}

vector<pair<int, string>> generateInput() {
    vector<pair<int, string>> inputs;
    int N = 100000;
    string S(3 * N, 'R');
    for (int i = 0; i < N; i++) {
        S[i] = 'G';
        S[2 * N + i] = 'B';
    }
    inputs.push_back({N, S});
    return inputs;
}