#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> generateInput() {
    vector<int> input;
    for (int i = 0; i < 200000; i++) {
        input.push_back(rand() % 26);
    }
    return input;
}

int baseline(string S) {
    int N = S.size();
    int A[26] = {};
    for (int i = 0; i < N; i++) {
        A[S[i] - 'a']++;
    }
    int kisuu = 0;
    for (int i = 0; i < 26; i++) {
        if (A[i] % 2) kisuu++;
    }
    if (kisuu > 1) return -1;

    vector<int> V1[26], V2[26];
    for (int i = 0; i < N; i++) {
        V1[S[i] - 'a'].push_back(i);
        V2[S[i] - 'a'].push_back(N - 1 - i);
    }

    int used[200001] = {};
    int kazu = 0;
    ll kotae = 0;
    int atta = 0;
    vector<int> BIT(200001, 0);

    auto add = [&](ll A) {
        while (A > 0) {
            BIT[A]++;
            A -= A & -A;
        }
    };

    auto query = [&](int A) {
        int kotae = 0;
        while (A <= 200000) {
            kotae += BIT[A];
            A += A & -A;
        }
        return kotae;
    };

    for (int i = 0; i < N; i++) {
        if (kazu * 2 >= N - 1) break;
        if (used[i] == 0) {
            int kari1 = V1[S[i] - 'a'].back();
            int kari2 = V2[S[i] - 'a'].back();
            if (i + kari2 == N - 1) {
                atta = 1;
                continue;
            }
            kotae += kari2 - query(kari1) + atta;
            used[kari1] = 1;
            add(kari1);
            V1[S[i] - 'a'].pop_back();
            V2[S[i] - 'a'].pop_back();
            kazu++;
        }
    }
    return kotae;
}