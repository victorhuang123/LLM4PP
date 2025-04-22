#pragma once

#include <bits/stdc++.h>

using namespace std;

using VS = vector<string>;    using LL = long long;
using VI = vector<int>;       using VVI = vector<VI>;
using PII = pair<int, int>;   using PLL = pair<LL, LL>;
using VL = vector<LL>;        using VVL = vector<VL>;

#define ALL(a)  begin((a)),end((a))
#define RALL(a) (a).rbegin(), (a).rend()
#define PB push_back
#define EB emplace_back
#define MP make_pair
#define SZ(a) int((a).size())
#define SORT(c) sort(ALL((c)))
#define RSORT(c) sort(RALL((c)))
#define UNIQ(c) (c).erase(unique(ALL((c))), end((c)))
#define FOR(i, s, e) for (int(i) = (s); (i) < (e); (i)++)
#define FORR(i, s, e) for (int(i) = (s); (i) > (e); (i)--)
#define debug(x) cerr << #x << ": " << x << endl

const int INF = 1e9;                          const LL LINF = 1e16;
const LL MOD = 1000000007;                    const double PI = acos(-1.0);
int DX[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };    int DY[8] = { 1, -1, 0, 0, 1, -1, 1, -1 };

LL baseline(const string& s) {
    VVI cnt(SZ(s) + 1, VI(26, 0));
    FOR(i, 0, SZ(s)) {
        FOR(j, 0, 26) {
            cnt[i + 1][j] += cnt[i][j] + (s[i] - 'a' == j);
        }
    }
    LL ans = 1;
    FOR(i, 0, SZ(s)) {
        ans += i - cnt[i][s[i] - 'a'];
    }
    return ans;
}

string generateInput() {
    string s(1000000, 'a');
    FOR(i, 0, SZ(s)) {
        s[i] = 'a' + (i % 26);
    }
    return s;
}