#pragma once

#include<bits/stdc++.h>

using namespace std;

#define faster_io ios_base::sync_with_stdio(0);

vector<int> baseline(int n, vector<int> a) {
    faster_io;

    int temp = 0, sum = 0, sum1;
    vector<int> b(n+2);
    a[0] = 0;
    a[n+1] = 0;

    for(int i = 1; i <= n; i++) {
        b[i] = abs(temp - a[i]);
        temp = a[i];
        sum += b[i];
    }

    b[n+1] = abs(a[n] - 0);
    sum += b[n+1];
    sum1 = sum;

    vector<int> result;
    for(int i = 0, j = 1; j <= n; i++, j++) {
        sum -= (b[j] + b[j+1]);
        sum += (abs(a[j-1] - a[j+1]));
        result.push_back(sum);
        sum = sum1;
    }

    return result;
}

vector<int> generateInput(int n) {
    vector<int> a(n+2);
    a[0] = 0;
    for(int i = 1; i <= n; i++) {
        a[i] = i;
    }
    a[n+1] = 0;
    return a;
}