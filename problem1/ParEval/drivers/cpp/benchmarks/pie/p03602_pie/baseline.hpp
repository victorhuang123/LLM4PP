#pragma once

#include <vector>

using namespace std;

long long baseline(int n, const vector<vector<int>>& a) {
    vector<vector<int>> b(n, vector<int>(n, 0));
    long long s = 0;

    for(int k=0; k<n; k++) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                int t = a[i][k] + a[k][j];
                if(a[i][j] > t) {
                    return -1;
                } else if(a[i][j] == t && k != i && k != j) {
                    b[i][j] = 1;
                }
            }
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            s += a[i][j] * !b[i][j];
        }
    }

    return s;
}

vector<vector<int>> generateInput(int n) {
    vector<vector<int>> a(n, vector<int>(n, 0));
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            a[i][j] = (i + j) % 1000; // Example input generation
        }
    }
    return a;
}