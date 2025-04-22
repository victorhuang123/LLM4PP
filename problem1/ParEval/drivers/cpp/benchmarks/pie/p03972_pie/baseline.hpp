#pragma once

#include<bits/stdc++.h>

using namespace std;

long long baseline(int w, int h, vector<long long>& a, vector<long long>& b) {
    long long asum[100005] = {0}, bsum[100005] = {0};

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    asum[0] = a[0];
    bsum[0] = b[0];

    for(int i = 1; i < w; i++) {
        asum[i] = asum[i - 1] + a[i];
    }
    for(int i = 1; i < h; i++) {
        bsum[i] = bsum[i - 1] + b[i];
    }

    long long sum = 0;
    for(int i = 0; i < h; i++) {
        long long p = upper_bound(a.begin(), a.end(), b[i]) - a.begin();
        if(p - 1 < 0) {
            sum += w * b[i];
        } else if(p == w) {
            sum += asum[p - 1];
        } else {
            sum += asum[p - 1];
            sum += (w - p) * b[i];
        }
    }

    return sum + asum[w - 1] + bsum[h - 1];
}

vector<long long> generateInput(int size) {
    vector<long long> input(size);
    for(int i = 0; i < size; i++) {
        input[i] = i + 1;
    }
    return input;
}