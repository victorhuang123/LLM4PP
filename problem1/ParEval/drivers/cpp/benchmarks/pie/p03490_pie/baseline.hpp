#pragma once

#include <bits/stdc++.h>
#include <utility>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> P;

bool accessible(int x, vector<int> v, vector<vector<int>>& dp) {
    int m = dp[0].size()/2, n=v.size();
    for(int i = 0; i < dp.size(); i++) for(int j = 0; j < dp[0].size(); j++) dp[i][j] = 0;
    dp[0][m] = 1;

    for(int i = 0; i < n; i++) {
        for(int j = -m; j < m; j++) {
            if(j+m-v[i] < 0 && j+m+v[i] < dp[0].size()) dp[i+1][j+m] = dp[i][j+m+v[i]];
            else if(j+m-v[i] > 0 && j+m+v[i] > dp[0].size()) dp[i+1][j+m] = dp[i][j+m-v[i]];
            else dp[i+1][j+m] = dp[i][j+m-v[i]] || dp[i][j+m+v[i]];
        }
    }

    return dp[n][x+m] == 1;
}

bool baseline(string s, int x, int y) {
    vector<int> fx(1, 0), fy(1, 0);
    int n = s.size();
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'F') {
            if(cnt%2==0) fx[cnt/2]++;
            else fy[cnt/2]++;
        } else if(s[i] == 'T') {
            cnt++;
            if(cnt%2==0) fx.push_back(0);
            else fy.push_back(0);
        }
    }
    if(cnt==s.size() && (x != 0 || y != 0)) {
        return false;
    }

    vector<vector<int>> dp(max(fx.size(), fy.size())+1, vector<int>(16001, 0));
    x -= fx[0];
    fx.erase(fx.begin());

    return accessible(x, fx, dp) && accessible(y, fy, dp);
}

vector<string> generateInput() {
    vector<string> inputs;
    string s(100000, 'F');
    inputs.push_back(s);
    return inputs;
}