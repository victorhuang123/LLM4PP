#pragma once

#include <vector>
#include <algorithm>

using namespace std;

#define rep(i,a,n) for(int (i)=(a); (i)<(n); (i)++)
#define repr(i,a,n) for(int (i)=(a); (i)>=(n); (i)--)
#define int long long int

int baseline(int n, vector<long long>& a, vector<long long>& b) {
    long long ans = 0;
    repr(i, n-1, 0) {
        long long k;
        a[i] += ans;
        if(a[i] == 0) k = 0;
        else if(a[i] < b[i]) k = b[i] - a[i];
        else {
            if(a[i] % b[i] == 0) k = 0;
            else k = b[i] - (a[i] % b[i]);
        }
        ans += k;
    }
    return ans;
}

vector<long long> generateInput(int n) {
    vector<long long> a(n), b(n);
    rep(i, 0, n) {
        a[i] = rand() % 1000000;
        b[i] = rand() % 1000000 + 1;
    }
    return a, b;
}