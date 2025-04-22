#pragma once

#include<bits/stdc++.h>
using namespace std;

vector<int> baseline(int N, int M, string S) {
    vector<int> dp(N + 1, 0);
    int mae = 0;
    int kazu = 0;
    while (mae <= N) {
        int tugi = mae + M;
        if (tugi > N) tugi = N;
        kazu++;
        int saigo = mae;
        for (int i = mae + 1; i <= tugi; i++) {
            if (S[i] == '0') {
                dp[i] = kazu;
                saigo = i;
            }
        }
        if (mae == saigo) break;
        mae = saigo;
    }

    if (dp[N] == 0) {
        return {};
    }

    vector<int> kotae;
    for (int i = N; i > 0;) {
        int k = dp[i];
        for (int j = max(0, i - M); j <= i; j++) {
            if (dp[j] == k - 1) {
                kotae.push_back(i - j);
                i = j;
                break;
            }
        }
    }

    reverse(kotae.begin(), kotae.end());
    return kotae;
}

vector<int> generateInput(int N, int M) {
    string S(N, '0');
    return baseline(N, M, S);
}