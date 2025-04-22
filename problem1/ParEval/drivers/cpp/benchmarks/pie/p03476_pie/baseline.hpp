#pragma once

#include<bits/stdc++.h>
using namespace std;

vector<int> generateInput(int N) {
    vector<int> input(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        input[i] = rand() % 500000 + 1;
    }
    return input;
}

int baseline(int N, const vector<int>& input, const vector<int>& like2017) {
    vector<int> like(500001, 0);
    for (int i = 0; i < 672; i++) {
        like[like2017[i]] = 1;
    }
    for (int i = 1; i <= 500000; i++) {
        like[i] += like[i - 1];
    }

    int result = 0;
    for (int i = 0; i < N; i++) {
        int l = input[2 * i] >> 1;
        int r = input[2 * i + 1] >> 1;
        result += like[r + 1] - like[l];
    }
    return result;
}