#pragma once

#include <bits/stdc++.h>

using namespace std;

pair<double, long long> baseline(int n, int l, int r, vector<long long>& a) {
    long long dp[300][300], sum[300][300];

    for(int i=0;i<=200;i++) {
        sum[0][i]=0;
        sum[i][0]=1;
        sum[i][i]=1;
    }

    for(int i=0;i<=200;i++) {
        for(int j=0;j<=200;j++) {
            dp[i][j]=-1;
        }
    }

    dp[0][0]=0;

    for(int i=1;i<=n;i++) {
        dp[i][0]=0;
        for(int j=1;j<=i&&j<=r;j++) {
            long long x=dp[i-1][j];
            long long y=dp[i-1][j-1]+a[i];
            if(x==y) {
                dp[i][j]=x;
                sum[i][j]=sum[i-1][j]+sum[i-1][j-1];
            } else if(x>y) {
                dp[i][j]=x;
                sum[i][j]=sum[i-1][j];
            } else {
                dp[i][j]=y;
                sum[i][j]=sum[i-1][j-1];
            }
        }
    }

    int pos=0;
    long long k=0;
    for(int i=l;i<=r&&i<=n;i++) {
        if(pos==0) {
            pos=i;
            k=sum[n][i];
        } else if(dp[n][i]*pos>dp[n][pos]*i) {
            pos=i;
            k=sum[n][i];
        } else if(dp[n][i]*pos==dp[n][pos]*i) {
            k+=sum[n][i];
        }
    }

    return {dp[n][pos] * 1.0 / pos * 1.0, k};
}

vector<long long> generateInput(int n) {
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}