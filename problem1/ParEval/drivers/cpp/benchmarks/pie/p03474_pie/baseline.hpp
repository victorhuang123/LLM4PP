#pragma once

#include <bits/stdc++.h>

using namespace std;

string baseline(int a, int b, string s) {
    int ans = 1;

    for(int i = 0; i < a; i++) {
        if(s[i] < '0' || s[i] > '9') {
            ans = 0;
            break;
        }
    }

    if(s[a] != '-')
        ans = 0;

    for(int i = a + 1; i < s.size(); i++) {
        if(s[i] < '0' || s[i] > '9') {
            ans = 0;
            break;
        }
    }

    return ans ? "Yes" : "No";
}

string generateInput() {
    int a = 1000000;
    int b = 1000000;
    string s(a + 1 + b, '0');
    s[a] = '-';
    return s;
}