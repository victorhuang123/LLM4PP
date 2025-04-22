#pragma once

#include<bits/stdc++.h>
using namespace std;

int baseline(int N, vector<pair<int, int>>& LR) {
    const int K = 18;
    const int KM = 1 << (K - 1);
    vector<int> dat(1 << K, 1e9);

    auto update = [&](int A) {
        dat[A] = min(dat[A * 2], dat[A * 2 + 1]);
        if (A != 1) update(A / 2);
    };

    auto add = [&](int A, int B) {
        int C = A + KM;
        dat[C] = B;
        update(C / 2);
    };

    auto check = [&](int L, int R, int A, int l, int r) {
        if (L <= l && r <= R) return dat[A];
        if (r <= L || R <= l) return 1e9;
        return min(check(L, R, A * 2, l, (l + r) / 2), check(L, R, A * 2 + 1, (l + r) / 2, r));
    };

    auto query = [&](int L, int R) {
        return check(L, R, 1, 0, KM);
    };

    int kotae = 0;
    sort(LR.begin(), LR.end());
    for (int i = 0; i < N; i++) add(i, LR[i].second);

    for (int i = 0; i < N; i++) {
        int l1 = LR[i].first;
        int r1 = LR[i].second;
        int lr1 = max(0, r1 - l1 + 1);
        int l2 = (i == N - 1) ? LR[N - 2].first : LR[N - 1].first;
        int r2 = min(query(i + 1, N), query(0, i));
        int lr2 = max(0, r2 - l2 + 1);
        kotae = max(kotae, lr1 + lr2);
    }

    for (int i = 0; i < N - 1; i++) {
        int l1 = LR[i].first;
        int r1 = query(0, i + 1);
        int lr1 = max(0, r1 - l1 + 1);
        int l2 = LR[N - 1].first;
        int r2 = query(i + 1, N);
        int lr2 = max(0, r2 - l2 + 1);
        kotae = max(kotae, lr1 + lr2);
    }

    return kotae;
}

vector<pair<int, int>> generate_input(int N) {
    vector<pair<int, int>> LR(N);
    for (int i = 0; i < N; i++) {
        LR[i].first = rand() % 1000000;
        LR[i].second = LR[i].first + rand() % 1000000;
    }
    return LR;
}