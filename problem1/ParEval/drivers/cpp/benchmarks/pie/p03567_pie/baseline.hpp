#pragma once

#include <bits/stdc++.h>

using namespace std;

string baseline(const string& s) {
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == 'A' && s[i + 1] == 'C') {
            return "Yes";
        }
    }
    return "No";
}

string generateInput() {
    string s(1000000, 'A');
    s[500000] = 'C';
    return s;
}