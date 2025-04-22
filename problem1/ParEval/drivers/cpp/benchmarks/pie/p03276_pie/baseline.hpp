#pragma once

#include <bits/stdc++.h>

using namespace std;

long long baseline(long long n, long long k, const vector<long long>& arr) {
    long long cost = LONG_LONG_MAX;
    for(int i=0;i<=n-k;i++){
        if(arr[i] < 0 && arr[i+k-1] <= 0){
            cost = min(cost, abs(arr[i]));
        }
        else if( arr[i]>=0 && arr[i+k-1] > 0){
            cost = min(cost, arr[i+k-1]);
        }
        else{
            cost= min(cost, min(abs(arr[i])*2+arr[i+k-1], abs(arr[i])+arr[i+k-1]*2));
        }
    }
    return cost;
}

vector<long long> generateInput(long long n) {
    vector<long long> arr(n);
    for(long long i = 0; i < n; ++i) {
        arr[i] = (i % 2 == 0) ? -i : i;
    }
    return arr;
}