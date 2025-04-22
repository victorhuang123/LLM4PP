#pragma once

#include<vector>
#include<algorithm>

using namespace std;

bool cool(int a, long long A, long long B, int N, const vector<long long>& s) {
    long long t = a;
    vector<long long> s1(s);
    for(int i = 1; i <= N; i++) {
        s1[i] -= a * B;
        if(s1[i] <= 0) continue;
        int y;
        if(s1[i] % (A - B) == 0) y = s1[i] / (A - B);
        else y = s1[i] / (A - B) + 1;
        t -= y;
    }
    return t >= 0;
}

long long baseline(int N, long long A, long long B, const vector<long long>& s) {
    long long l = 0, L = 1000000009, s1 = 1000000009;
    while(l < L) {
        long long man = (l + L) / 2;
        if(cool(man, A, B, N, s)) L = man, s1 = min(s1, man);
        else l = man + 1;
    }
    return s1;
}

vector<long long> generateInput(int N) {
    vector<long long> s(N + 1);
    for(int i = 1; i <= N; i++) {
        s[i] = 1000000000000LL; // Large value to maximize problem scale
    }
    return s;
}