#pragma once

#include <vector>
#include <algorithm>

using namespace std;

long long baseline(int D, int N, int M, const vector<int>& S_input, const vector<int>& T_input) {
    vector<int> S(N + 1);
    vector<int> T(M);

    S[0] = 0;
    S[N] = D;

    for (int i = 1; i < N; i++) { S[i] = S_input[i - 1]; }
    for (int i = 0; i < M; i++) { T[i] = T_input[i]; }

    sort(S.begin(), S.end());

    long long distance_ = 0;

    for (int i = 0; i < M; i++) {
        int l = *(upper_bound(S.begin(), S.end(), T[i]) - 1);
        int r = *lower_bound(S.begin(), S.end(), T[i]);

        distance_ += min(T[i] - l, r - T[i]);
    }

    return distance_;
}

vector<int> generateInput(int size) {
    vector<int> input(size);
    for (int i = 0; i < size; i++) {
        input[i] = i + 1;
    }
    return input;
}