#pragma once

#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7, MAX = 1e6;

struct Template {
    vector<int> SPF;
    vector<int> Primes;
    int sz;
};

Template P;

void ready() {
    P.SPF.resize(MAX + 1, 0);
    P.Primes.resize(168, 0);
    P.SPF[0] = 1;
    P.Primes[0] = 2;
    P.sz = 1;
    for (int i = 0; i < MAX / 2; ++i) {
        P.SPF[2 * (i + 1)] = 2;
        P.SPF[2 * (i + 1) - 1] = 2 * (i + 1) - 1;
    }
    for (int i = 0; i < MAX / 2 - 1; ++i) {
        int x = 2 * (i + 1) + 1;
        if (P.SPF[x] == x) {
            P.Primes[P.sz++] = x;
        }
        if (x * x > MAX) break;
        for (int j = 0; j < P.sz; ++j) {
            if (P.Primes[j] <= P.SPF[x] && x * P.Primes[j] <= MAX) {
                P.SPF[x * P.Primes[j]] = P.Primes[j];
            } else {
                break;
            }
        }
    }
}

int GCD(int a, int b) {
    return !b ? a : GCD(b, a % b);
}

bool Divise(int x, vector<vector<int>>& esc, int& vol) {
    if (!x) return false;
    for (int i = 0; i < 168; ++i) {
        if (x % P.Primes[i]) continue;
        for (int j = 0; j < vol; ++j) {
            if (esc[j][0] == P.Primes[i] && esc[j][1]) return false;
        }
        esc[vol][0] = P.Primes[i];
        esc[vol++][1] = 1;
        while (x % P.Primes[i] == 0) {
            x /= P.Primes[i];
        }
    }
    if (x != 1) {
        for (int j = 0; j < vol; ++j) {
            if (esc[j][0] == x && esc[j][1]) return false;
        }
        esc[vol][0] = x;
        esc[vol++][1] = 1;
        return true;
    }
    return true;
}

int baseline(const vector<int>& A) {
    int g = 0;
    int flag = 0;
    vector<vector<int>> esc(100, vector<int>(2, 0));
    int vol = 0;
    ready();
    for (int i = 0; i < A.size(); ++i) {
        g = GCD(g, A[i]);
        if (!Divise(A[i], esc, vol)) {
            flag = 1;
        }
    }
    if (flag) return 0;
    if (g == 1) return 1;
    return 2;
}

vector<int> generateInput() {
    vector<int> A(MAX);
    for (int i = 0; i < MAX; ++i) {
        A[i] = i + 1;
    }
    return A;
}