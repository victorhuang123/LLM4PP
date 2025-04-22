#pragma once

#include<bits/stdc++.h>
using namespace std;

vector<long long> generateInput() {
    vector<long long> input = {1000000000, 1000000000};
    return input;
}

long long baseline(long long A, long long P) {
    A *= 3;
    A += P;
    return A / 2;
}