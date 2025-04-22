#pragma once

#include <algorithm>
#include <vector>
#include <cstring>
#define INF 100005

using namespace std;

int baseline(const vector<char>& str) {
    int F[INF][2];
    memset(F, 0x0f, sizeof(F));
    F[1][1] = F[1][0] = 0;
    int len = str.size();
    int X[3] = {3, 1, 2};

    auto getnum = [&](char c0, char c1) {
        return X[(c0 - 48) % 3] <= X[(c1 - 48) % 3];
    };

    for (int i = 2; i <= len; i++) {
        F[i][0] = min(F[i][0], F[i - 1][0] + 1);
        if (getnum(str[i - 1], str[i - 2]))
            F[i][0] = min(F[i][0], F[i - 1][1]);
        F[i][1] = min(F[i][1], F[i - 1][1] + 1);
        if (getnum(str[i - 2], str[i - 1]))
            F[i][1] = min(F[i][1], F[i - 1][0]);
    }
    return min(F[len][0], F[len][1]);
}

vector<char> generateInput() {
    vector<char> str(INF - 1, '1');
    return str;
}