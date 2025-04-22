#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)
#define rep1(i, n) for(int i = 1; i <= (n); i++)

vector<pair<int, int>> baseline(int N, int M) {
    vector<pair<int, int>> result;
    if (N % 2) {
        rep1(i, M) {
            result.push_back(make_pair(i, N - i));
        }
    } else {
        int n = N / 2;
        rep1(i, (M + 1) / 2) {
            result.push_back(make_pair(i, N - i + 1));
        }
        for (int i = (M + 1) / 2 + 1; i <= M; i++) {
            result.push_back(make_pair(i, N - i));
        }
    }
    return result;
}