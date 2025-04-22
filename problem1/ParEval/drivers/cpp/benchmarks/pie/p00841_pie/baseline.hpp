#pragma once

#include<vector>
#include<algorithm>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;

double baseline(int n, vector<int>& a, double b, int r, double v, double e, double f) {
    n++;
    vector<double> t(a[n-1] + 1, 0);
    rep(x, a[n-1]) {
        if(x < r) t[x+1] = t[x] + 1/(v - f*(r - x));
        else t[x+1] = t[x] + 1/(v - e*(x - r));
    }

    vector<vector<double>> dp(n, vector<double>(a[n-1] + 1, 1e60));
    dp[0][0] = 0;

    for(int i = 1; i < n; i++) {
        int dis = a[i] - a[i-1];
        for(int x = dis; x <= a[n-1]; x++) {
            dp[i][x] = min(dp[i][x], dp[i-1][x-dis] + t[x] - t[x-dis]);
            dp[i][0] = min(dp[i][0], dp[i][x] + b);
        }
    }

    return *min_element(dp[n-1].begin(), dp[n-1].end());
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        a[i] = i * 100;
    }
    return a;
}