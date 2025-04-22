#pragma once

#include <vector>
#include <algorithm>

using namespace std;

long long baseline(long n, vector<long>& a) {
    vector<vector<long long> > gp(n+1, vector<long long>(n+1, 0));

    for(long i=0; i<n; i++) {
        gp[i][0] = a[i];
    }

    for(long j=1; j<n; j++) {
        for(long i=0; i<n-j; i++) {
            gp[i][j] = max(a[i]-gp[i+1][j-1], a[i+j]-gp[i][j-1]);
        }
    }

    return gp[0][n-1];
}

vector<long> generateInput(long n) {
    vector<long> a(n);
    for(long i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}