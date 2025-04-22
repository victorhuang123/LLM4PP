#pragma once

#include<bits/stdc++.h>

using namespace std;

string baseline(const string& s) {
    string result;
    for (int i = 0; i < s.length(); i += 2) {
        result += s[i];
    }
    return result;
}

string generateInput() {
    string s(1000000, 'a');
    for (int i = 0; i < s.length(); ++i) {
        s[i] = 'a' + (i % 26);
    }
    return s;
}