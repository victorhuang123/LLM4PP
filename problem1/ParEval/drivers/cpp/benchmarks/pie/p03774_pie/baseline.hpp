#pragma once

#include<bits/stdc++.h>
using namespace std;

vector<int> baseline(int n, int m, vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d) {
    vector<int> result;
    for(int i = 0; i < n; i++) {
        int mini = INT_MAX;
        int minIndex = 0;
        for(int j = 0; j < m; j++) {
            int dist = abs(a[i] - c[j]) + abs(b[i] - d[j]);
            if(dist < mini) {
                mini = dist;
                minIndex = j + 1;
            }
        }
        result.push_back(minIndex);
    }
    return result;
}

vector<int> generateInput(int size) {
    vector<int> input(size);
    for(int i = 0; i < size; i++) {
        input[i] = rand() % 1000000;
    }
    return input;
}