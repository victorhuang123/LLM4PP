#pragma once

#include<bits/stdc++.h>

using namespace std;

string baseline(const string& a, const string& b) {
    int la = a.length(), lb = b.length();
    int i = 0, j = 0;
    string result;
    while (i < la && j < lb) {
        result += a[i++];
        result += b[j++];
    }
    while (i < la)
        result += a[i++];
    while (j < lb)
        result += b[j++];
    return result;
}

string generateInput() {
    string a(100000, 'a');
    string b(100000, 'b');
    return baseline(a, b);
}