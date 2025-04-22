#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mod 1000000007

string baseline(int A, vector<int>& a, int B, vector<int>& b) {
    map<int, int> mpa, mpb;

    for(int i = 0; i < A; i++) {
        mpa[a[i]]++;
    }

    for(int i = 0; i < B; i++) {
        mpb[b[i]]++;
    }

    for(int i = 0; i < B; i++) {
        int x = b[i];
        if(mpb[x] > mpa[x]) {
            return "NO";
        }
    }
    return "YES";
}

vector<int> generateInput(int size) {
    vector<int> input(size);
    for(int i = 0; i < size; i++) {
        input[i] = i + 1;
    }
    return input;
}