#pragma once

#include <vector>

using namespace std;

const int MAX = 100000, mod = 1e9+7;

vector<int> generateInput(int n) {
    vector<int> input(n);
    for (int i = 0; i < n; i++) {
        input[i] = i % MAX;
    }
    return input;
}

int baseline(int n, const vector<int>& input) {
    vector<int> A(MAX, 0);
    long long sum = 1;
    A[0] = 3;

    for (int i = 0; i < n; i++) {
        int a = input[i];
        sum = (sum * A[a]) % mod;
        A[a]--;
        A[a+1]++;
    }

    return sum;
}