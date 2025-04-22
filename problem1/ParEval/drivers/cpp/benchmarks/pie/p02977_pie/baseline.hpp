#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<double> VD;
#define MP make_pair
#define PB push_back
#define X first
#define Y second

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define RFOR(i, b, a) for(int i = (b) - 1; i >= (a); --i)
#define ITER(it, a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define ALL(a) a.begin(), a.end()
#define SZ(a) (int)((a).size())
#define FILL(a, value) memset(a, value, sizeof(a))
#define debug(a) cout << #a << " = " << a << endl;

const double PI = acos(-1.0);
const LL INF = 1e9 + 47;
const LL LINF = INF * INF;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<PII> baseline(int n) {
    vector<PII> e;
    if (__builtin_popcount(n) == 1) {
        return e;
    }

    for(int i = 2; i <= n - 1; i += 2) {
        e.PB({1, i});
        e.PB({i, i + 1});
        e.PB({1, n + i + 1});
        e.PB({n + i + 1, n + i});
    }

    e.PB({n + 1, n + 2});

    if (n % 2 == 0) {
        int ksor = n ^ (n - 1);
        e.PB({2 * n, 2 * n - 1});
        e.PB({n, ksor - 1});
    }

    assert(SZ(e) == 2 * n - 1);
    return e;
}

vector<int> generateInput() {
    int n = 1 << 18;
    return {n};
}