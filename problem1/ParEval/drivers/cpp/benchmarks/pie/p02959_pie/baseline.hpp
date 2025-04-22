#pragma once

#include<vector>
#include<algorithm>

using namespace std;

long long baseline(long long n, vector<long long>& a, vector<long long>& b) {
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        if(b[i] >= a[i]) {
            sum += a[i];
            b[i] -= a[i];
            if(b[i] >= a[i+1]) {
                sum += a[i+1];
                a[i+1] = 0;
            } else {
                sum += b[i];
                a[i+1] -= b[i];
            }
        } else {
            sum += b[i];
        }
    }
    return sum;
}

vector<long long> generateInput(long long n) {
    vector<long long> a(n + 1), b(n);
    for(long long i = 0; i < n; i++) {
        a[i] = 1000000000LL;
        b[i] = 1000000000LL;
    }
    a[n] = 1000000000LL;
    return {a, b};
}