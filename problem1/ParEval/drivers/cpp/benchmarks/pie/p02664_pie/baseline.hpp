#pragma once

#include<bits/stdc++.h>

using namespace std;

string baseline(const string& s) {
    string result = s;
    for (char& c : result) {
        if (c == '?') {
            c = 'D';
        }
    }
    return result;
}

string generateInput() {
    string s;
    for (int i = 0; i < 1000000; ++i) {
        s += (i % 2 == 0) ? 'A' : '?';
    }
    return s;
}