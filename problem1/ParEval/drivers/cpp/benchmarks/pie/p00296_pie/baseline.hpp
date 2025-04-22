#pragma once

#include <vector>

using namespace std;

vector<int> baseline(int N, int M, int Q, const vector<int>& operations) {
    vector<int> prv(N), nxt(N);
    for (int i = 0; i < N; i++) {
        prv[i] = (i + N - 1) % N;
        nxt[i] = (i + 1) % N;
    }

    int p = 0, r = 0;
    for (int i = 0; i < M; i++) {
        int a = operations[i];
        for (int j = 0; j < a; j++) {
            p = a % 2 ? prv[p] : nxt[p];
        }
        nxt[prv[p]] = nxt[p];
        prv[nxt[p]] = prv[p];
        r = nxt[p];
        prv[p] = nxt[p] = -1;
        p = r;
    }

    vector<int> result(Q);
    for (int i = 0; i < Q; i++) {
        int a = operations[M + i];
        result[i] = (prv[a] != -1 ? 1 : 0);
    }
    return result;
}

vector<int> generateInput(int N, int M, int Q) {
    vector<int> operations(M + Q);
    for (int i = 0; i < M; i++) {
        operations[i] = rand() % N;
    }
    for (int i = M; i < M + Q; i++) {
        operations[i] = rand() % N;
    }
    return operations;
}