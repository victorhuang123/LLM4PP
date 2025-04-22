#pragma once

#include<vector>
#include<algorithm>

using namespace std;

typedef long long int ll;

ll baseline(int N, const vector<ll>& A) {
    vector<vector<ll>> memo(N, vector<ll>(2 * N, -1));

    auto memoize = [&](int i, int j, auto&& memoize) -> ll {
        if (memo[i][j] != -1) return memo[i][j];

        int i2 = (i == N - 1 ? 0 : i + 1);
        int j2 = (j == 0 ? N - 1 : j - 1);
        int itv = (i > j ? N + j - i : j - i);

        if ((N - itv) % 2 == 1) {
            if (i == j) return memo[i][j] = A[i];
            else return memo[i][j] = max(memoize(i2, j, memoize) + A[i], memoize(i, j2, memoize) + A[j]);
        } else {
            if (i == j) return memo[i][j] = 0LL;
            else if (A[i] > A[j]) return memo[i][j] = memoize(i2, j, memoize);
            else return memo[i][j] = memoize(i, j2, memoize);
        }
        return 0;
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            memo[i][j] = memoize(i, j, memoize);
        }
    }

    ll res = 0LL;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            res = max(res, memo[i][j]);
        }
    }

    return res;
}

vector<ll> generateInput(int N) {
    vector<ll> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = static_cast<ll>(i + 1) * 1000000000LL;
    }
    return A;
}