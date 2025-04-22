#pragma once

#include<vector>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

#define MAX_N 1000000
#define INF 1145141145141919810LL

long long baseline(long long h, long long w, long long n, vector<long long>& x, vector<long long>& y) {
    long long lx[MAX_N], ly[MAX_N], d[MAX_N], sx = 0, sy = 0, c, mx = INF, my = INF, minx = INF, dx, dy, sum;
    vector<long long> X, Y, BX, BY;

    for(int i = 0; i < n; i++) {
        lx[i] = x[i];
        ly[i] = y[i];
        sx += x[i];
        sy += y[i];
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    for(int i = 0; i < n; i++) {
        if(i == 0) { c = x[0]; }
        else { c = x[i] - x[i-1]; }
        sx += (-n + i*2) * c;
        if(mx == sx) { X.push_back(x[i]); }
        if(mx > sx) { mx = sx; X.clear(); X.push_back(x[i]); }
    }

    for(int i = 0; i < n; i++) {
        if(i == 0) { c = y[0]; }
        else { c = y[i] - y[i-1]; }
        sy += (-n + i*2) * c;
        if(my == sy) { Y.push_back(y[i]); }
        if(my > sy) { my = sy; Y.clear(); Y.push_back(y[i]); }
    }

    for(int i = 0; i < X.size(); i++) {
        if(i < 10) { BX.push_back(X[i]); }
        else { if(X[i] != X[i-10]) { BX.push_back(X[i]); } }
    }

    for(int i = 0; i < Y.size(); i++) {
        if(i < 10) { BY.push_back(Y[i]); }
        else { if(Y[i] != Y[i-10]) { BY.push_back(Y[i]); } }
    }

    for(int i = 0; i < BX.size(); i++) {
        for(int j = 0; j < BY.size(); j++) {
            memset(d, 0, sizeof(d));
            sum = 0;
            for(int k = 0; k < n; k++) {
                d[k] = abs(BX[i] - lx[k]) + abs(BY[j] - ly[k]);
                sum += d[k] * 2;
            }
            sort(d, d + n);
            sum -= d[n-1];
            if(minx > sum) {
                minx = sum;
                dx = BX[i];
                dy = BY[j];
            }
        }
    }

    return minx;
}

vector<long long> generateInput(long long n) {
    vector<long long> x(n), y(n);
    for(long long i = 0; i < n; i++) {
        x[i] = i;
        y[i] = i;
    }
    return x, y;
}