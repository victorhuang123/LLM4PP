#pragma once

#include <vector>

using namespace std;

int baseline(int N, const vector<int>& a) {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (a[a[i] - 1] - 1 == i) {
            cnt++;
        }
    }
    return cnt / 2;
}

vector<int> generateInput(int N) {
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = (i % N) + 1;
    }
    return a;
}