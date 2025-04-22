#pragma once

#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 1e6;

struct Template {
    vector<int> SPF;
    vector<int> Primes;
    int sz;
};

Template P;

int MPow(int a, int b) {
    return b ? 1LL * MPow(1LL * a * a % MOD, b >> 1) * (b & 1 ? a : 1) % MOD : 1;
}

void ready() {
    P.SPF.resize(MAX + 1);
    P.Primes.resize(168);
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

int count(const int prime, const vector<int>& A) {
    int max = 0;
    for (int a : A) {
        int now = 0;
        while (a % prime == 0) {
            now++;
            a /= prime;
        }
        if (max < now) max = now;
    }
    return max;
}

int baseline(const vector<int>& A) {
    int N = A.size();
    int x = 0;
    ready();
    vector<int> tempA = A;
    for (int a : tempA) {
        x = (x + 1LL * MPow(a, MOD - 2)) % MOD;
    }
    for (int i = 0; i < 168; ++i) {
        x = 1LL * x * MPow(P.Primes[i], count(P.Primes[i], tempA)) % MOD;
    }
    for (int i = 0; i < N; ++i) {
        if (tempA[i] > 1) {
            for (int j = i + 1; j < N; ++j) {
                if (tempA[i] == tempA[j]) {
                    tempA[j] = 1;
                }
            }
            x = 1LL * x * tempA[i] % MOD;
        }
    }
    return x;
}

vector<int> generateInput() {
    vector<int> input(10000);
    for (int i = 0; i < 10000; ++i) {
        input[i] = rand() % MAX + 1;
    }
    return input;
}