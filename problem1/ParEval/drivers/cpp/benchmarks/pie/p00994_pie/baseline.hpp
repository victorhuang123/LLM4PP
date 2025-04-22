#pragma once

#include<vector>
#include<cstring>

using namespace std;

const int mod = (int)1e8 + 7;

int baseline(int h, int w, vector<vector<char>>& in) {
    int pw[11];
    pw[0] = 1;
    for(int i = 0; i < 10; i++) pw[i + 1] = pw[i] * 3;

    int dp[2][11][3][60000];
    int cur = 0, next = 1;
    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = 1;

    for(int i = 0; i < h; i++) {
        memset(dp[next], 0, sizeof(dp[next]));
        for(int j = 0; j < w; j++) {
            for(int l = 0; l < 3; l++) {
                for(int u = 0; u < pw[w]; u++) {
                    if(dp[cur][j][l][u]) {
                        int tu = u / pw[j] % 3;

                        if(in[i][j] == '.') {
                            if(tu && l) continue;
                            (dp[cur][j + 1][l][u] += dp[cur][j][l][u]) %= mod;
                            continue;
                        }
                        int rest = in[i][j] - '0' - tu - l;
                        for(int nl = 0; nl < 3; nl++) {
                            int nu = rest - nl;
                            if(nu < 0 || nu > 2) continue;
                            (dp[cur][j + 1][nl][u + pw[j] * (nu - tu)] += dp[cur][j][l][u]) %= mod;
                        }
                    }
                }
            }
        }
        for(int u = 0; u < pw[w]; u++) dp[next][0][0][u] = dp[cur][w][0][u];
        swap(cur, next);
    }
    return dp[cur][0][0][0];
}

vector<vector<char>> generateInput(int h, int w) {
    vector<vector<char>> in(h, vector<char>(w));
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            in[i][j] = '1' + (i + j) % 2;
        }
    }
    return in;
}