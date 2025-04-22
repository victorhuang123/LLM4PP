#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll baseline(const string& s) {
    ll n = s.size();
    queue<ll> a;
    queue<ll> b;
    ll up = 0;
    ll down = 0;

    for (ll i = 0; i < n; i++) {
        if (i == 0 && s[0] == '>') {
            a.push(0);
            down++;
        }
        if (i != 0 && s[i] == '>') {
            if (up) {
                a.push(up);
                up = 0;
            }
            down++;
        }
        if (s[i] == '<') {
            if (down) {
                b.push(down);
                down = 0;
            }
            up++;
        }
        if (i == n - 1) {
            if (up) a.push(up);
            b.push(down);
        }
    }
    b.push(0);

    vector<ll> c(500010);
    c[0] = 0;
    for (ll i = 0; i < 500010; i++) c[i + 1] = c[i] + i + 1;

    ll ans = 0;
    while (!a.empty()) {
        if (a.front() >= b.front()) {
            ans += c[a.front()] + c[max(b.front() - 1, 0ll)];
            a.pop();
            b.pop();
        } else {
            ans += c[max(0ll, a.front() - 1)] + c[b.front()];
            a.pop();
            b.pop();
        }
    }
    return ans;
}

string generateInput() {
    string s(500000, '>');
    for (int i = 0; i < 500000; i += 2) {
        s[i] = '<';
    }
    return s;
}