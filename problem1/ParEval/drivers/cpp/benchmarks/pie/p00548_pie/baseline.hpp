#pragma once

#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int baseline(int N, int M, int K, vector<int>& A) {
    vector<int> memo(N + 1, -1);

    function<int(int)> rec = [&](int now) {
        if (memo[now] != -1) return memo[now];

        int res = INT_MAX;
        int mi = INT_MAX, ma = INT_MIN;

        for (int i = 0, to = min(N - now, M); i < to; ++i) {
            mi = min(mi, A[now + i]);
            ma = max(ma, A[now + i]);

            res = min(res, K + (ma - mi) * (i + 1) + rec(now + i + 1));
        }

        if (res == INT_MAX) res = 0;

        return memo[now] = res;
    };

    return rec(0);
}

vector<int> generateInput(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = rand() % 1000000 + 1;
    }
    return A;
}