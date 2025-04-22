#pragma once

#include<vector>
#include<cmath>

struct Point {
    double x, y, z;
};

double baseline(int N, int M, const std::vector<Point>& P) {
    std::vector<std::vector<double>> Rel(N, std::vector<double>(N, 0.0));
    double Ans = 0, tmp;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            Rel[i][j] = Rel[j][i] = (P[i].x - P[j].x) * (P[i].x - P[j].x) +
                                    (P[i].y - P[j].y) * (P[i].y - P[j].y) +
                                    (P[i].z - P[j].z) * (P[i].z - P[j].z);
        }
    }

    for (int s = 1; s < (1 << N); s++) {
        if (__builtin_popcount(s) == M) {
            tmp = 0;
            for (int i = 0; i < N; i++) {
                if (s & (1 << i)) {
                    for (int j = i + 1; j < N; j++) {
                        if (s & (1 << j)) {
                            tmp += Rel[i][j];
                        }
                    }
                }
            }
            if (tmp > Ans) {
                Ans = tmp;
            }
        }
    }

    return Ans;
}

std::vector<Point> generateInput(int N) {
    std::vector<Point> P(N);
    for (int i = 0; i < N; i++) {
        P[i].x = static_cast<double>(rand()) / RAND_MAX;
        P[i].y = static_cast<double>(rand()) / RAND_MAX;
        P[i].z = static_cast<double>(rand()) / RAND_MAX;
    }
    return P;
}