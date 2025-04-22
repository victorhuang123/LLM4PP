#pragma once

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define RFOR(i,b,a) for(int i = (b) - 1; i >= (a); i--)
#define ITER(it, a) for(typeof(a.begin()) it = a.begin(); it != a.end(); it++)
#define FILL(a, value) memset(a, value, sizeof(a))

#define SZ(a) (int) a.size()
#define ALL(a) a.begin(),a.end()
#define PB push_back
#define MP make_pair

typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> PII;

const double PI = acos(-1.0);
const LL INF = 1000 * 1000 * 1000 + 7;
const LL LINF = INF * (LL)INF;

bool intersect(LL x1, LL y1, LL x2, LL y2)
{
    if (y1 < x2) return false;
    if (y2 < x1) return false;
    return true;
}

bool baseline(LL n, LL a, LL b, LL c, LL d)
{
    vector<LL> L(n), R(n), U(n), D(n);

    L[0] = R[0] = a;
    FOR (i, 1, n)
    {
        L[i] = L[i-1] + c;
        R[i] = R[i-1] + d;
    }

    U[n-1] = D[n-1] = b;
    RFOR(i, n-1, 0)
    {
        D[i] = D[i+1] + c;
        U[i] = U[i+1] + d;
    }

    FOR (i, 0, n)
    {
        if (intersect(L[i], R[i], D[i], U[i]))
        {
            return true;
        }
    }

    return false;
}

vector<LL> generateInput()
{
    LL n = 500000;
    LL a = 1, b = 1, c = 1, d = 1;
    return {n, a, b, c, d};
}