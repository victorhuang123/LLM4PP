#pragma once

#include <algorithm>
#include <vector>

using namespace std;

long long baseline(int N, int M, const vector<char>& S, const vector<char>& T) {
    int g = __gcd(N, M);
    int stepS = N / g;
    int stepT = M / g;
    for (int i = 0; i < g; ++i) {
        if (S[stepS * i] != T[stepT * i]) {
            return -1;
        }
    }
    return (long long) N / g * M;
}

vector<char> generateInput(int N, char c) {
    return vector<char>(N, c);
}