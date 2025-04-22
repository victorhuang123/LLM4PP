#pragma once

#include<bits/stdc++.h>

using namespace std;

string baseline(int n, const string& s) {
    string t;
    for(int i = 0; i < (int)s.size(); ++i) {
        int c = (int)s[i] - 'A';
        c = (c + n) % 26;
        t += (char)c + 'A';
    }
    return t;
}

string generateInput() {
    string s;
    for(int i = 0; i < 1000000; ++i) {
        s += 'A' + (i % 26);
    }
    return s;
}