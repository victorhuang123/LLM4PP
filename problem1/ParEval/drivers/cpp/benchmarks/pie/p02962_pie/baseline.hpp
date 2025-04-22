#pragma once

#include <vector>
#include <algorithm>

std::vector<int> generateInput() {
    std::vector<int> input(2000001);
    for (int i = 0; i < 2000001; ++i) {
        input[i] = i % 26 + 'a';
    }
    return input;
}

int baseline(const std::vector<char>& t, const std::vector<char>& s, int K) {
    int N = t.size();
    std::vector<int> v(2000001, 0);
    std::vector<int> quef(1000001, 0);
    std::vector<int> ques(1000001, 0);
    int size = 0;

    int ng = 500001;
    while (ng - K > 1) {
        int mid = (ng + K) >> 1;
        (s[mid] ? K : ng) = mid;
    }

    int i = 0, j = 0;
    while (i < N) {
        s[K + i] = t[i];
        ++i;
    }
    N = i;
    i += K;
    while (i < 2000001) {
        s[i++] = t[j++];
        j *= j < N;
    }
    N = (K + N - 1) / N * N;

    i = 1;
    j = 0;
    while (i < N) {
        while (i + j < N && s[i + j] == s[j]) ++j;
        v[i] = j;
        if (!j) {
            ++i;
            continue;
        }
        int k = 1;
        while (v[k] + k < j) {
            v[i + k] = v[k];
            ++k;
        }
        i += k;
        j -= k;
    }

    for (i = 0; i < N; ++i) {
        if (v[i + K] < K) ques[size++] = i + K - (i + K >= N) * N;
    }

    for (i = 0; i < N; ++i) {
        if (i == size) {
            return -1;
        }
        if (v[ques[i] += K] >= K) {
            ques[size] = ques[i] - N * (ques[i] >= N);
            quef[size++] = quef[i] + 1;
        }
    }
    return quef[N - 1];
}