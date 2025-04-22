#pragma once

#include <vector>
#include <cstring>

typedef long long llt;

const llt Mod = 1e9 + 7;

struct Matrix {
    std::vector<std::vector<llt>> mat;
    Matrix(int N) : mat(N, std::vector<llt>(N, 0)) {}
};

inline Matrix operator * (const Matrix& A, const Matrix& B) {
    int N = A.mat.size();
    Matrix C(N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % Mod;
    return C;
}

inline Matrix operator ^ (Matrix low, llt high) {
    int N = low.mat.size();
    Matrix res(N);
    for (int i = 0; i < N; ++i) res.mat[i][i] = 1;
    while (high) {
        if (high & 1) res = res * low;
        high >>= 1;
        low = low * low;
    }
    return res;
}

llt baseline(int N, llt K, const Matrix& G) {
    Matrix result = G ^ K;
    llt res = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            res = (res + result.mat[i][j]) % Mod;
    return res;
}

Matrix generateInput(int N) {
    Matrix G(N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            G.mat[i][j] = rand() % Mod;
    return G;
}