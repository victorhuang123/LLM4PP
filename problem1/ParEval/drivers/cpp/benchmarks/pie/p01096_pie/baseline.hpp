#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int n, vector<int>& w) {
    vector<vector<int>> maxx(n, vector<int>(n, 0));
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for(int i=0;i<n-1;i++)
        if(abs(w[i]-w[i+1])<=1)
            dp[i][i+1]=1;

    for(int k=2;k<=n;k++)
        for(int i=0;i+k<n;i++) {
            if(dp[i+1][i+k-1]==1&&abs(w[i]-w[i+k])<=1)
                dp[i][i+k]=1;
            else
                for(int j=i+1;j<i+k-1;j++)
                    if(dp[i][j]==1&&dp[j+1][i+k]==1) {
                        dp[i][i+k]=1;
                        break;
                    }
        }

    for(int k=1;k<n;k++)
        for(int i=0;i+k<n;i++) {
            if(dp[i][i+k]==1)
                maxx[i][i+k]=k+1;
            else
                for(int j=i;j<i+k;j++)
                    if(maxx[i][i+k]<maxx[i][j]+maxx[j+1][i+k])
                        maxx[i][i+k]=maxx[i][j]+maxx[j+1][i+k];
        }

    return maxx[0][n-1];
}

vector<int> generateInput(int n) {
    vector<int> w(n);
    for(int i = 0; i < n; i++) {
        w[i] = rand() % 100;
    }
    return w;
}