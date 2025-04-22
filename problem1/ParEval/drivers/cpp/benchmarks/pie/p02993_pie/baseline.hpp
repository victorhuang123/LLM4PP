#pragma once

#include<bits/stdc++.h>

using namespace std;

string generateInput() {
    string s(1000000, 'a');
    for (int i = 1; i < 1000000; i += 2) {
        s[i] = 'b';
    }
    return s;
}

bool baseline(const string& s) {
    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i] == s[i-1]) {
            return false;
        }
    }
    return true;
}