#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int baseline(int n, int m, vector<pair<int, int>>& inputs) {
    int a[10];
    map<int, int> q;
    int flag = 1;
    memset(a, -1, sizeof(a));

    for (auto& input : inputs) {
        int s = input.first;
        int c = input.second;
        if (q.count(s) == 0) {
            q[s] = c;
            a[s] = c;
        } else {
            if (q[s] != c) flag = 0;
        }
    }

    if (a[1] == 0 && n > 1) flag = 0;
    if (flag == 0) return -1;
    else {
        int result = 0;
        if (n > 1) {
            for (int i = 1; i <= n; i++) {
                if (a[i] == -1 && i == 1) result = result * 10 + 1;
                else if (a[i] == -1 && i > 1) result = result * 10 + 0;
                else result = result * 10 + a[i];
            }
        } else {
            if (a[1] == -1) result = 0;
            else result = a[1];
        }
        return result;
    }
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> inputs;
    for (int i = 0; i < m; i++) {
        int s = rand() % n + 1;
        int c = rand() % 10;
        inputs.push_back({s, c});
    }
    return inputs;
}