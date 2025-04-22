#pragma once

#include<bits/stdc++.h>
using namespace std;
#define int long long

vector<int> generateInput(int n) {
    vector<int> input(n);
    for(int i = 0; i < n; i++) {
        input[i] = rand() % 1000000 + 1;
    }
    return input;
}

string baseline(const vector<int>& input) {
    int dem = 0;
    for(int x : input) {
        if(x % 2 == 1) {
            dem = 1;
            break;
        }
    }
    return (dem == 0) ? "second" : "first";
}