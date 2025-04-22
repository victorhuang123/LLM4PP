#pragma once

#include <vector>
#include <string>

std::vector<int> baseline(int N, const std::vector<std::string>& S) {
    int A = 0, W = 0, T = 0, R = 0;

    for (int i = 0; i < N; i++) {
        if (S[i] == "AC") {
            A++;
        } else if (S[i] == "WA") {
            W++;
        } else if (S[i] == "TLE") {
            T++;
        } else if (S[i] == "RE") {
            R++;
        }
    }

    return {A, W, T, R};
}

std::vector<std::string> generateInput(int N) {
    std::vector<std::string> S(N);
    for (int i = 0; i < N; i++) {
        int randVal = rand() % 4;
        if (randVal == 0) {
            S[i] = "AC";
        } else if (randVal == 1) {
            S[i] = "WA";
        } else if (randVal == 2) {
            S[i] = "TLE";
        } else {
            S[i] = "RE";
        }
    }
    return S;
}