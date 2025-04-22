#pragma once

#include<bitset>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long ll;

ll baseline(ll h, ll w, vector<vector<ll>>& a, vector<vector<ll>>& b) {
    ll mid = 14000;
    vector<vector<bitset<28000>>> dp(h, vector<bitset<28000>>(w));

    dp[0][0][mid + a[0][0] - b[0][0]] = true;
    dp[0][0][mid - a[0][0] + b[0][0]] = true;

    for (ll i = 0; i < h; i++) {
        for (ll j = 0; j < w; j++) {
            if (i + j > 0) {
                bitset<28000> temp;
                if (i == 0) temp = dp[i][j-1];
                else if (j == 0) temp = dp[i-1][j];
                else temp = dp[i-1][j] | dp[i][j-1];

                ll x = abs(a[i][j] - b[i][j]);
                dp[i][j] = (temp >> x) | (temp << x);
            }
        }
    }

    for (ll i = 0;; i++) {
        if (dp[h-1][w-1][mid-i] || dp[h-1][w-1][mid+i]) {
            return i;
        }
    }
}

vector<vector<ll>> generateInput(ll h, ll w) {
    vector<vector<ll>> a(h, vector<ll>(w));
    vector<vector<ll>> b(h, vector<ll>(w));

    for (ll i = 0; i < h; i++) {
        for (ll j = 0; j < w; j++) {
            a[i][j] = j + 1;
            b[i][j] = w - j;
        }
    }

    return a, b;
}