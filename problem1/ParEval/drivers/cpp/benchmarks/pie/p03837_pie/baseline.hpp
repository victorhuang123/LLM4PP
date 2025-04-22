#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

int baseline(int N, int M, vector<tuple<int, int, int>>& edges) {
    int A[101][101] = {};
    rep1(i, 100) {
        rep1(ii, 100) {
            if (i != ii) A[i][ii] = 10000000;
        }
    }

    for (auto& edge : edges) {
        int a = get<0>(edge);
        int b = get<1>(edge);
        int c = get<2>(edge);
        A[a][b] = c;
        A[b][a] = c;
    }

    int B[101][101] = {};
    rep1(k, N) {
        rep1(i, N) {
            rep1(j, N) {
                if (A[i][k] + A[k][j] < A[i][j]) {
                    B[i][j] = 1;
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
    }

    int goukei = 0;
    rep1(i, N) {
        rep1(ii, N) {
            if (B[i][ii]) goukei++;
        }
    }
    int hennmax = N * (N - 1) / 2;

    return goukei / 2 + M - hennmax;
}

vector<tuple<int, int, int>> generateInput(int N) {
    vector<tuple<int, int, int>> edges;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.push_back(make_tuple(i, j, 1));
        }
    }
    return edges;
}