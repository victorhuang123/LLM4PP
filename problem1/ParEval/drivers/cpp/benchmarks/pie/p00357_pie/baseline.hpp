#pragma once

#include <bits/stdc++.h>

using namespace std;

string baseline(int n, vector<int>& d) {
    for (int i = 0; i < n; i++) {
        int sub = d[i] % 10;
        d[i] -= sub;
    }

    int nowpos = 0;
    int canhop = 0;
    int maxhop = 0;

    for (int j = 0; j < 300000; j++) {
        canhop = d[nowpos] / 10 + nowpos;
        maxhop = canhop;
        if (canhop >= n - 1) {
            nowpos = n - 1;
            canhop = nowpos - d[nowpos] / 10;
            int minhop = canhop;
            if (canhop <= 0) return "yes";

            for (int i = nowpos; i >= canhop; i--) {
                if (i - d[i] / 10 < minhop) {
                    nowpos = i;
                    minhop = i - d[i] / 10;
                }
            }
            return "no";
        }

        for (int i = nowpos; i <= canhop; i++) {
            if (d[i] / 10 + i >= maxhop) {
                nowpos = i;
                maxhop = d[i] / 10 + i;
            }
        }
    }
    return "no";
}

vector<int> generateInput(int n) {
    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        d[i] = rand() % 1000000 + 1;
    }
    return d;
}