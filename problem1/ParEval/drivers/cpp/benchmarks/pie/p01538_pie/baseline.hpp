#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int N) {
    vector<bool> table(1000001, false);
    int count = 0;
    table[N] = true;

    while (true) {
        if (N / 10 == 0) break;

        int max_val = 0;

        for (int S = 10; N / S != 0; S *= 10) {
            int tmp = (N / S) * (N % S);
            max_val = max(max_val, tmp);
        }

        N = max_val;
        if (table[N]) {
            return -1;
        } else {
            table[N] = true;
            count++;
        }
    }

    return count;
}

vector<int> generateInput() {
    return {999999};
}