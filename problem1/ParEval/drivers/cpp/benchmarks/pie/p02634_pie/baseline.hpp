#pragma once

#include <bits/stdc++.h>

using namespace std;

const long long mod = 998244353;

struct mint {
    long long x;
    mint(long long x=0):x((x%mod+mod)%mod){}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += mod-a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator*=(const mint a) {
        (x *= a.x) %= mod;
        return *this;
    }
    mint operator+(const mint a) const {
        mint res(*this);
        return res+=a;
    }
    mint operator-(const mint a) const {
        mint res(*this);
        return res-=a;
    }
    mint operator*(const mint a) const {
        mint res(*this);
        return res*=a;
    }
    mint pow(long long t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }
    mint inv() const {
        return pow(mod-2);
    }
    mint& operator/=(const mint a) {
        return (*this) *= a.inv();
    }
    mint operator/(const mint a) const {
        mint res(*this);
        return res/=a;
    }
};

mint baseline(int a, int b, int c, int d) {
    vector<vector<mint>> dp(c+100, vector<mint>(d+100, 0));
    dp[a][b] = 1;
    for(int i = 0; i < c; i++) {
        for(int j = 0; j < d; j++) {
            dp[i+1][j+1] += dp[i+1][j] * (i+1) + dp[i][j+1] * (j+1) - dp[i][j] * i * j;
        }
    }
    return dp[c][d];
}

vector<int> generateInput() {
    return {0, 0, 1000, 1000};
}