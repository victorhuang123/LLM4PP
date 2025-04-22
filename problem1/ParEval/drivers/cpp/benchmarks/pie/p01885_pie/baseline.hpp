#pragma once

#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct P {
    ll dif; int id;
    P(ll dif = 0, int id = -1) :dif(dif), id(id) {}
    P operator + (const P &a) const { return P(dif + a.dif, id); }
    bool operator < (const P &a) const { return dif > a.dif; }
};

int baseline(int n, ll L, const vector<ll>& a, const vector<ll>& b, const vector<ll>& c) {
    vector<P> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = P(a[i] - b[i], i);
    }
    vector<ll> prefix_c = c;
    for (int i = 1; i < n; i++) {
        prefix_c[i] += prefix_c[i - 1];
    }
    sort(p.begin(), p.end());
    vector<int> loc(n);
    for (int i = 0; i < n; i++) {
        loc[p[i].id] = i;
    }
    int fu = n - 1;
    for (; fu >= 0 && p[fu].dif <= 0; fu--);
    for (int i = 1; i < n; i++) {
        p[i] = p[i] + p[i - 1];
    }
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < n; i++) {
        ll len = L - a[i];
        int l = -1, r = fu;
        if (len <= 0) { ans = min(ans, 1); continue; }
        while (r - l > 1) {
            int mid = l + r >> 1;
            if (p[mid].dif - a[p[loc[i]].id] + b[p[loc[i]].id] < len) l = mid;
            else r = mid;
        }
        int now = r - (r >= loc[i]);
        ll v = p[r].dif - (r >= loc[i] ? a[p[loc[i]].id] - b[p[loc[i]].id] : 0);
        if (v >= len && v > prefix_c[now]) {
            ans = min(ans, now + 2);
        }
    }
    return ans;
}

vector<ll> generateInput(int n) {
    vector<ll> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000000 + 1;
        b[i] = rand() % 1000000 + 1;
        c[i] = rand() % 1000000 + 1;
    }
    return a, b, c;
}