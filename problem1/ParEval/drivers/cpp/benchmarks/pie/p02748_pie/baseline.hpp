#pragma once

#include<bits/stdc++.h>
using namespace std;

int baseline(int A, int B, int M, vector<int>& a, vector<int>& b, vector<tuple<int, int, int>>& offers) {
    int kotae = *min_element(a.begin() + 1, a.begin() + A + 1) + *min_element(b.begin() + 1, b.begin() + B + 1);

    for (auto& offer : offers) {
        int x = get<0>(offer);
        int y = get<1>(offer);
        int c = get<2>(offer);
        int tmp = a[x] + b[y] - c;
        kotae = min(kotae, tmp);
    }

    return kotae;
}

vector<int> generate_a(int A) {
    vector<int> a(A + 1);
    for (int i = 1; i <= A; i++) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}

vector<int> generate_b(int B) {
    vector<int> b(B + 1);
    for (int i = 1; i <= B; i++) {
        b[i] = rand() % 1000000 + 1;
    }
    return b;
}

vector<tuple<int, int, int>> generate_offers(int M, int A, int B) {
    vector<tuple<int, int, int>> offers(M);
    for (int i = 0; i < M; i++) {
        int x = rand() % A + 1;
        int y = rand() % B + 1;
        int c = rand() % 1000000 + 1;
        offers[i] = make_tuple(x, y, c);
    }
    return offers;
}