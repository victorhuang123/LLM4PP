#pragma once

#include<bits/stdc++.h>
using namespace std;

int baseline(vector<string> S) {
    int L[3];
    for(int i = 0; i < 3; i++) L[i] = S[i].size();

    bool dame[3][3][4020] = {};
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (i != j) {
                for(int k = 0; k < L[i]; k++) {
                    int ok = 1;
                    int k2 = min(L[i] - k, L[j]);
                    for(int x = 0; x < k2; x++) {
                        if (S[i][k + x] != '?' && S[j][x] != '?' && S[i][k + x] != S[j][x]) {
                            ok = 0;
                            break;
                        }
                    }
                    if (!ok) dame[i][j][k] = 1;
                }
            }
        }
    }

    int P[3] = { 0,1,2 };
    int saishou = 6000;
    for(int x = 0; x < 6; x++) {
        int i = P[0];
        int j = P[1];
        int k = P[2];

        for(int p = 0; p <= L[i]; p++) {
            if (!dame[i][j][p]) {
                for(int q = 0; q < 4010; q++) {
                    if (!dame[j][k][q] && !dame[i][k][p + q]) {
                        saishou = min(saishou, max({ L[i], L[j] + p, L[k] + p + q }));
                        break;
                    }
                }
            }
        }
        next_permutation(P, P + 3);
    }

    return saishou;
}

vector<string> generateInput() {
    vector<string> S(3);
    for(int i = 0; i < 3; i++) {
        S[i] = string(2000, '?');
        for(int j = 0; j < 2000; j++) {
            if (j % 2 == 0) S[i][j] = 'a' + (j % 26);
        }
    }
    return S;
}