#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

bool baseline(int n, const vector<int>& a, const vector<int>& b) {
    ll tot_a = 0, tot_b = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) {
            int diff = b[i] - a[i];
            if (diff % 2) {
                tot_a += (diff + 1) / 2;
                tot_b++;
            } else {
                tot_a += diff / 2;
            }
        } else {
            tot_b += (a[i] - b[i]);
        }
    }

    return tot_a >= tot_b;
}

vector<int> generateInput(int n) {
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000000;
        b[i] = rand() % 1000000;
    }
    return a, b;
}