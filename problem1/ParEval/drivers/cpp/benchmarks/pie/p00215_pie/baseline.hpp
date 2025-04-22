#pragma once

#include<vector>
#include<algorithm>
#include<climits>
#include<cstring>
using namespace std;

typedef pair<int, int> P;

int baseline(int x, int y, vector<vector<char>>& mas) {
    vector<P> point[7];
    int dp[6][1001][6];
    int cx[6], ans;
    int sp, ans1;

    for(int i = 0; i < 7; i++) {
        point[i].clear();
    }
    memset(cx, 0, sizeof(cx));
    ans1 = INT_MAX;
    sp = INT_MAX;

    for(int i = 0; i < y; i++) {
        for(int j = 0; j < x; j++) {
            if(mas[i][j] == 'S') {
                point[0].push_back(P(j,i));
            }
            if(mas[i][j] == 'G') {
                point[6].push_back(P(j,i));
            }
            if(mas[i][j] >= '1' && mas[i][j] <= '5') {
                point[mas[i][j] - '0'].push_back(P(j,i));
                cx[mas[i][j] - '0']++;
            }
        }
    }

    for(int i = 1; i <= 5; i++) {
        rotate(point + 1, point + 2, point + 6);
        rotate(cx + 1, cx + 2, cx + 6);
        memset(dp, -1, sizeof(dp));
        ans = solve(0, 0, 0, dp, point, cx);
        if(ans < ans1) {
            ans1 = ans;
            sp = i;
        }
    }

    if(ans1 == INT_MAX) return -1;
    else return sp * 1000000 + ans1;
}

int solve(int i, int j, int z, int dp[6][1001][6], vector<P> point[7], int cx[6]) {
    if(dp[i][j][z] >= 0) return dp[i][j][z];
    if(i == 4) {
        return abs(point[6][0].first - point[z][j].first) + abs(point[6][0].second - point[z][j].second);
    }
    int res = INT_MAX;
    for(int k = 0; k < cx[z + 1]; k++) {
        res = min(abs(point[z + 1][k].first - point[z][j].first) + abs(point[z + 1][k].second - point[z][j].second) + solve(i + 1, k, z + 1, dp, point, cx), res);
    }
    return dp[i][j][z] = res;
}

vector<vector<char>> generateInput(int x, int y) {
    vector<vector<char>> mas(y, vector<char>(x, '.'));
    mas[0][0] = 'S';
    mas[y-1][x-1] = 'G';
    for(int i = 1; i < y-1; i++) {
        for(int j = 1; j < x-1; j++) {
            if((i + j) % 5 == 0) {
                mas[i][j] = '1' + (i + j) % 5;
            }
        }
    }
    return mas;
}