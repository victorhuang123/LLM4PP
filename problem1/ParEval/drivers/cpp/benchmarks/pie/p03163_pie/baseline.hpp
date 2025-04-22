#pragma once

#include<vector>
#include<algorithm>

using namespace std;

typedef unsigned long long ULL;

ULL baseline(ULL N, ULL w, const vector<ULL>& W, const vector<ULL>& Value) {
    vector<ULL> f(w + 1, 0);

    for (ULL i = 1; i <= N; i++) {
        for (ULL j = w; j >= W[i]; j--) {
            f[j] = max(f[j], f[j - W[i]] + Value[i]);
        }
    }

    return f[w];
}

vector<ULL> generateInput(ULL N, ULL w) {
    vector<ULL> W(N + 1), Value(N + 1);
    for (ULL i = 1; i <= N; i++) {
        W[i] = i % 100 + 1;
        Value[i] = i % 100 + 1;
    }
    return {W, Value};
}