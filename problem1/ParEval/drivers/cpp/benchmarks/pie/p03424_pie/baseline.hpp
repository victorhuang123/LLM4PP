#pragma once

#include<bits/stdc++.h>

using namespace std;

string baseline(int n, const vector<char>& num) {
    set<char> color(num.begin(), num.end());
    return color.size() == 4 ? "Four" : "Three";
}

vector<char> generateInput(int n) {
    vector<char> num(n);
    for (int i = 0; i < n; ++i) {
        num[i] = 'A' + (i % 4);
    }
    return num;
}