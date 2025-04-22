#pragma once

#include <bits/stdc++.h>

using namespace std;

long long baseline(long long n, long long K, vector<long long>& a) {
    long long F[60][2601] = {0};
    long long ans = 0, tmp[60][2601] = {0};
    
    F[0][0] = 1;
    
    for(int i = 1; i <= n; i++) {
        memset(tmp, 0, sizeof tmp);
        for(int j = 0; j < i; j++) {
            for(int k = 0; k <= 2501; k++) {
                tmp[j+1][k+a[i-1]] += F[j][k];
                tmp[j][k] += F[j][k];
            }
        }
        for(int j = 0; j <= i; j++) {
            for(int k = 0; k <= 2501; k++) {
                F[j][k] = tmp[j][k];
            }
        }
    }
    
    for(int i = 1; i <= n; i++) {
        if(i * K <= 2500) {
            ans += F[i][i * K];
        }
    }
    
    return ans;
}

vector<long long> generateInput(long long n) {
    vector<long long> a(n);
    for(long long i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}