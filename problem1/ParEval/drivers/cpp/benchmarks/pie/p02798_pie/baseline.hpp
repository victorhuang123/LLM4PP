#pragma once

#include<bits/stdc++.h>
using namespace std;

int baseline(int N, vector<int>& A, vector<int>& B) {
    vector<vector<int>> dp(1 << N, vector<int>(18, -1));

    function<int(int, bool, int)> keisan = [&](int b, bool bp, int k) {
        if (b && dp[b][k] != -1) return dp[b][k];
        if (b == (1 << N) - 1) return 0;

        int k2 = (bp ^ (k & 1)) ? A[k] : B[k];
        int saishou = 2e9;
        int num2 = 0;
        for (int i = 0; i < N; i++) {
            if (!(b >> i & 1)) {
                if ((bp ^ i) & 1) {
                    if (B[i] >= k2) {
                        saishou = min(saishou, keisan(b ^ (1 << i), !bp, i) + num2);
                    }
                } else {
                    if (A[i] >= k2) {
                        saishou = min(saishou, keisan(b ^ (1 << i), !bp, i) + num2);
                    }
                }
                num2++;
            }
        }
        return dp[b][k] = saishou;
    };

    int kotae = keisan(0, 0, 18);
    return (kotae > 1e9) ? -1 : kotae;
}

vector<int> generateInput(int N) {
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 1000000;
        B[i] = rand() % 1000000;
    }
    return {A, B};
}