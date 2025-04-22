#pragma once

#include<vector>
#include<cmath>

using namespace std;

struct node {
    double t, p;
};

long long c[51][51] = {0};

void prepare() {
    c[0][0] = 1; c[1][0] = 1;
    for (int i = 1; i < 51; i++) {
        for (int j = 0; j < 51; j++) {
            if (j == 0) c[i][j] = 1;
            else c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }
}

vector<double> baseline(int N, int M, int L, const vector<double>& p, const vector<double>& t, const vector<double>& v) {
    prepare();
    vector<vector<node>> per(N, vector<node>(M + 1));
    vector<double> result(N);

    for (int i = 0; i < N; i++) {
        per[i][0].t = L / v[i];
        per[i][0].p = pow(1 - p[i], M);
        for (int j = 1; j <= M; j++) {
            per[i][j].p = c[M][j] * pow(1 - p[i], M - j) * pow(p[i], j);
            per[i][j].t = per[i][j - 1].t + t[i];
        }
    }

    for (int i = 0; i < N; i++) {
        double s = 0;
        for (int j = 0; j <= M; j++) {
            double tt = per[i][j].p;
            for (int k = 0; k < N; k++) {
                if (k != i) {
                    double ts = 0;
                    for (int t = M; t >= 0 && per[k][t].t > per[i][j].t; t--) {
                        ts += per[k][t].p;
                    }
                    tt *= ts;
                }
            }
            s += tt;
        }
        result[i] = s;
    }

    return result;
}

vector<double> generateInput(int N, int M, int L) {
    vector<double> p(N), t(N), v(N);
    for (int i = 0; i < N; i++) {
        p[i] = 0.5;
        t[i] = 1.0;
        v[i] = 1.0;
    }
    return baseline(N, M, L, p, t, v);
}