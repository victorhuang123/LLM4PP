#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int a, int b, int c, const vector<int>& s) {
    int js = 0;

    for(int i = 0; i < a; i++) {
        if(s[i] >= c || s[i] < b)
            js++;
    }

    return js;
}

vector<int> generateInput(int a) {
    vector<int> s(a);
    for(int i = 0; i < a; i++) {
        s[i] = i + 1;
    }
    return s;
}