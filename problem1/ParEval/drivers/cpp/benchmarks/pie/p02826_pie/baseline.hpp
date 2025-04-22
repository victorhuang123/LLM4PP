#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long

#define REP(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)

#define DREP(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)

#define fi first

#define se second

#define mkr(a,b) make_pair(a,b)

#define SZ(A) ((int)A.size())

template<class T>inline void chkmin(T &a,T b){ if(a>b)a=b;}

template<class T>inline void chkmax(T &a,T b){ if(a<b)a=b;}

inline void pls(int &a,int b, int mod){ a+=b; a-=a>=mod?mod:0;}

int baseline(int n, int mod)
{
    vector<int> dp(n+1, 0);
    vector<vector<int>> f(n+1, vector<int>(n+1, 0));

    int len = (n-1) >> 1;
    dp[0] = 1;

    REP(i, 1, len + (~n & 1))
    {
        int w = i;
        for(int j = w; j <= n; j++)
            pls(dp[j], dp[j-w], mod);
    }

    f[0][0] = 1;
    REP(i, 1, n)
    {
        REP(j, 0, n) f[i][j] = f[i-1][j];
        REP(j, i, n) pls(f[i][j], f[i][j-i], mod);
    }

    DREP(i, n, 1)
    {
        int s = 0;
        REP(j, 0, n)
        {
            pls(s, f[i-1][j], mod);
            int nj = j + len + 1;
            if(nj <= n) pls(f[i][nj], mod - s, mod);
        }
    }

    int ans = 0;
    REP(x, 1, n)
    {
        int a = x - 1, mx = n - x;
        int suf = 0;
        DREP(j, a, 0)
        {
            suf = (suf + dp[a-j]) % mod;
            ans = (ans + (ll)suf * f[mx][j]) % mod;
        }
    }

    return ans;
}

vector<int> generate_input(int n, int mod)
{
    return {n, mod};
}