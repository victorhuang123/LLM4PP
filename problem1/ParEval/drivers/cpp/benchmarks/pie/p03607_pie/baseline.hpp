#pragma once

#include<bits/stdc++.h>

using namespace std;

long long baseline(long long N, vector<string>& A) {
    long long total = 0;
    map<string, bool> number;

    for(int i = 0; i < N; i++) {
        number[A[i]] = false;
    }

    for(int i = 0; i < N; i++) {
        if(number[A[i]] == false) {
            number[A[i]] = true;
            total += 1;
        } else {
            number[A[i]] = false;
            total -= 1;
        }
    }

    return total;
}

vector<string> generateInput(long long N) {
    vector<string> A(N);
    for(long long i = 0; i < N; i++) {
        A[i] = "a" + to_string(i % 1000);
    }
    return A;
}