#pragma once

#include<bits/stdc++.h>

using namespace std;

bool baseline(int N, int M, vector<int>& A) {
    vector<int> dp(100001, -1);

    auto Check = [&](int k) {
        fill(dp.begin(), dp.end(), -1);
        dp[0] = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j <= M; j++) {
                if(dp[j] >= 0) {
                    dp[j] = k;
                } else if(j < A[i] || dp[j - A[i]] <= 0) {
                    dp[j] = -1;
                } else {
                    dp[j] = dp[j - A[i]] - 1;
                }
            }
        }
        return(dp[M] >= 0);
    };

    sort(A.begin(), A.end(), greater<int>());
    int low = 0, high = M;
    while(high - low > 0) {
        int mid = (low + high) >> 1;
        if(Check(mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

vector<int> generateInput(int N, int M) {
    vector<int> A(N);
    for(int i = 0; i < N; i++) {
        A[i] = rand() % M + 1;
    }
    return A;
}