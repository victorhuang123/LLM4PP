#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll baseline(int N, int K, vector<int>& H) {
    ll hutuu = 0;
    for (int i = 0; i < N; i++) {
        if (H[i + 1] > H[i]) hutuu += H[i + 1] - H[i];
    }

    ll dp[302][601] = {};
    for (int i = 0; i <= N; i++) {
        auto dpi = dp[i];
        ll tmp1 = max(0, H[i + 1] - H[i]);
        ll tmp2 = max(0, H[i] - H[i + 1]);
        ll tmp3 = min(tmp1, tmp2);
        int mae = H[i + 1];
        ll maetmp = tmp3;
        for (int j = i + 2; j <= N + 1; j++) {
            if (mae < H[j]) tmp1 += H[j] - mae;
            if (mae > H[j]) tmp2 += mae - H[j];
            tmp3 = min(tmp1, tmp2);
            if (maetmp < tmp3) {
                int k = j - i - 1;
                auto dpj = dp[j] + k;
                for (int p = 0; p < K; p++) dpj[p] = max(dpj[p], dpi[p] + tmp3);
            }
            mae = H[j];
            maetmp = tmp3;
        }
        auto dpi2 = dp[i + 1];
        for (int p = 0; p <= K; p++) dpi2[p] = max(dpi2[p], dpi[p]);
    }
    return hutuu - dp[N + 1][K];
}

vector<int> generateInput(int N) {
    vector<int> H(N + 2);
    for (int i = 0; i <= N; i++) {
        H[i] = i;
    }
    for (int i = N + 1; i >= 0; i--) {
        H[i] = N - i;
    }
    return H;
}