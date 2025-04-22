#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<int> generateInput(int n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}

long long baseline(int n, vector<int>& a) {
    sort(a.begin() + 1, a.end());

    long long jum = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            jum += lower_bound(a.begin() + j + 1, a.end(), a[i] + a[j]) - (a.begin() + j + 1);
        }
    }

    return jum;
}