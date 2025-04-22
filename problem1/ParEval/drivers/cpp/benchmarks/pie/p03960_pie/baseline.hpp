#pragma once

#include <bits/stdc++.h>

using namespace std;

#define MODULE 1000000007
#define MP make_pair
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second

template<class T, class U>
inline void chmin(T &t, U f) { if (t > f)t = f; }

template<class T, class U>
inline void chmax(T &t, U f) { if (t < f)t = f; }

typedef pair<int, int> P;
typedef long long LL;
const LL INF = LLONG_MAX / 2;
const int MAXN = 100001;

template<typename A, size_t N, typename T>
void Fill(A (&array)[N], const T &val){
    std::fill( (T*)array, (T*)(array+N), val );
}

LL baseline(int h, int w, vector<string>& color) {
    vector<vector<LL>> cost(301,vector<LL>(301));
    vector<vector<LL>> dp(301,vector<LL>(301,INF));
    LL sum = 0;

    for (int i = 0; i < w - 1; ++i) {
        for (int j = 0; j <= h; ++j)
            for (int k = 0; k <= h; ++k){
                if (j == 0 || k == 0) {
                    LL tmp = 0;
                    for (int l = 0; l < h; ++l) {
                        if (l - j >= 0 && l - k >= 0 && color[l - j][i] == color[l - k][i + 1])
                            tmp++;
                    }
                    cost[j][k] = tmp;
                } else {
                    cost[j][k] = cost[j - 1][k - 1] - (color[h - j][i] == color[h - k][i + 1] ? 1 : 0);
                }
            }

        for (int j = 0; j < 301; ++j) {
            fill(dp[j].begin(),dp[j].end(),INF);
        }

        dp[0][0] = 0;
        for (int j = 0; j <= h; ++j) {
            for (int k = 0; k <= h; ++k) {
                LL tmpA = j > 0 ? dp[j - 1][k] + cost[j - 1][k] : INF;
                LL tmpB = k > 0 ? dp[j][k - 1] + cost[j][k - 1] : INF;
                chmin(dp[j][k], min(tmpA, tmpB));
            }
        }
        sum += dp[h][h];
    }
    return sum;
}

vector<string> generateInput(int h, int w) {
    vector<string> color(h, string(w, 'A'));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            color[i][j] = 'A' + (i + j) % 26;
        }
    }
    return color;
}