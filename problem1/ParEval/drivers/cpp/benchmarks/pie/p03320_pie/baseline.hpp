#pragma once

#include <vector>
#include <algorithm>

long long sum(long long X) {
    long long res = 0;
    while(X) res += X%10, X/=10;
    return res;
}

long long nxt(long long X) {
    long long mn = X;
    long long p = 1;
    long long other = 0;
    long long cur = X;
    while(cur) {
        other += p * 9;
        cur /= 10;
        p *= 10;
        if(mn * sum(cur * p + other) > (cur * p + other) * sum(mn)) mn = cur * p + other;
    }
    return mn;
}

long long baseline(int K) {
    long long cur = 1;
    while(--K) {
        cur = nxt(cur+1);
    }
    return cur;
}

std::vector<int> generateInput() {
    return {1000000};
}