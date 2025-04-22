#pragma once

#include <vector>
#include <algorithm>

#define N_F 1010
#define N_CONST 1001

using namespace std;

unsigned long long int f[N_F];
vector<vector<int>> node(N_CONST + 10, vector<int>(N_CONST + 10, 0));

void rmNode(int i) {
    node[i][i] = 0;
    for (int j = 0; j < N_CONST; j++) {
        if (node[j][j] == 0)
            continue;
        if (node[i][j] == 1) {
            rmNode(j);
        }
    }
}

int baseline(int v, int d) {
    f[0] = 1;  f[1] = 2;
    for (int i = 2; i < N_F; i++) {
        f[i] = (f[i-1] + f[i-2]) % N_CONST;
    }

    for (int i = 1; i <= v; i++) {
        int f1 = f[i] % N_CONST;
        node[f1][f1] = 1;

        for (int j = 1; j <= v; j++) {
            int f2 = f[j] % N_CONST;
            if (abs(f1 - f2) < d) {
                node[f1][f2] = 1;
                node[f2][f1] = 1;
            }
        }
    }

    int n = 0;
    for (int i = 0; i < N_CONST; i++) {
        if (node[i][i] == 0)
            continue;
        n++;
        rmNode(i);
    }
    return n;
}

vector<int> generateInput() {
    return {N_CONST, N_CONST / 2};
}