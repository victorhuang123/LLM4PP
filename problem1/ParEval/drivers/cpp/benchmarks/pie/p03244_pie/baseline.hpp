#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int n, const vector<int>& arr) {
    vector<int> a1(100005, 0);
    int m1 = 0;
    int p1 = 0;
    vector<int> a2(100005, 0);
    int m2 = 0;
    int p2 = 0;

    for (int i = 0; i < n; i++) {
        int tmp = arr[i];
        if (i % 2 == 0) {
            a1[tmp]++;
            if (a1[tmp] > m1) {
                m1 = a1[tmp];
                p1 = tmp;
            }
        }
        if (i % 2 == 1) {
            a2[tmp]++;
            if (a2[tmp] > m2) {
                m2 = a2[tmp];
                p2 = tmp;
            }
        }
    }

    if (p1 == p2) {
        int M1 = 0;
        int M2 = 0;
        for (int i = 0; i <= 100000; i++) {
            if (i == p1) continue;
            M1 = max(M1, a1[i]);
            M2 = max(M2, a2[i]);
        }
        return n - max(m1 + M2, m2 + M1);
    } else {
        return n - m1 - m2;
    }
}

vector<int> generateInput(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i % 100000 + 1;
    }
    return arr;
}