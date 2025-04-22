#pragma once

#include<bits/stdc++.h>

using namespace std;

#define M 1000000

vector<int> generateInput() {
    vector<int> list(M);
    for (int i = 0; i < M; ++i) {
        list[i] = i + 2;
    }
    return list;
}

int baseline(vector<int> list) {
    int m = INT_MIN, val;
    for(int num : list) {
        m = max(m, num);
    }
    val = m-1;
    while(1) {
        bool found = true;
        for(int x: list) {
            if(val % x != x - 1) {
                found = false;
                break;
            }
        }
        if(found) {
            return val;
        }
        val += m;
    }
}