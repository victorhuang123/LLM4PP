#pragma once

#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

vector<int> generateInput(int N) {
    vector<int> X(N), Y(N), H(N);
    for (int i = 0; i < N; i++) {
        X[i] = rand() % 101;
        Y[i] = rand() % 101;
        H[i] = rand() % 201;
    }
    return {X, Y, H};
}

vector<int> baseline(int N, vector<int>& X, vector<int>& Y, vector<int>& H) {
    int minheight = *min_element(H.begin(), H.end());

    vector<vector<vector<int>>> A(101, vector<vector<int>>(101, vector<int>(N)));
    vector<vector<int>> M(101, vector<int>(101)), m(101, vector<int>(101));

    for (int x = 0; x <= 100; x++) {
        for (int y = 0; y <= 100; y++) {
            for (int i = 0; i < N; i++) {
                A[x][y][i] = H[i] + abs(x - X[i]) + abs(y - Y[i]);
            }
        }
    }

    int ansx = 0, ansy = 0, ansh = 0;

    if (minheight > 0) {
        for (int x = 0; x <= 100; x++) {
            for (int y = 0; y <= 100; y++) {
                M[x][y] = A[x][y][0];
                m[x][y] = A[x][y][0];
            }
        }

        for (int x = 0; x <= 100; x++) {
            for (int y = 0; y <= 100; y++) {
                for (int i = 1; i < N; i++) {
                    M[x][y] = max(M[x][y], A[x][y][i]);
                    m[x][y] = min(m[x][y], A[x][y][i]);
                }
            }
        }

        for (int x = 0; x <= 100; x++) {
            for (int y = 0; y <= 100; y++) {
                if (M[x][y] == m[x][y]) {
                    ansx = x;
                    ansy = y;
                    ansh = M[x][y];
                }
            }
        }
    } else if (minheight == 0) {
        for (int x = 0; x <= 100; x++) {
            for (int y = 0; y <= 100; y++) {
                for (int h = 1; h <= 200; h++) {
                    bool valid = true;
                    for (int i = 0; i < N; i++) {
                        if (max(h - abs(x - X[i]) - abs(y - Y[i]), 0) != H[i]) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        ansx = x;
                        ansy = y;
                        ansh = h;
                    }
                }
            }
        }
    }

    return {ansx, ansy, ansh};
}