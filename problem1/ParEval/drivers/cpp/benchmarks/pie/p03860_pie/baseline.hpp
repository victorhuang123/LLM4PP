#pragma once

#include<bits/stdc++.h>

using namespace std;

string generateInput() {
    string input;
    for (int i = 0; i < 1000000; ++i) {
        input += "aBcDeFgHiJkLmNoPqRsTuVwXyZ ";
    }
    return input;
}

string baseline(const string& a) {
    string result;
    int len = a.length();
    if (len > 0) {
        result += a[0];
    }
    for (int i = 1; i < len; i++) {
        if (a[i] >= 'A' && a[i] <= 'Z' && a[i - 1] == ' ') {
            result += a[i];
        }
    }
    return result;
}