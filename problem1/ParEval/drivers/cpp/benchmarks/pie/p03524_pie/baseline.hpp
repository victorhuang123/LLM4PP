#pragma once

#include <bits/stdc++.h>
using namespace std;

string baseline(const string& s) {
    int cnt[150] = {0};
    int n = s.size();

    for (int i = 0; i < n; i++) {
        cnt[s[i]]++;
    }

    if (abs(cnt['a'] - cnt['b']) > 1 || abs(cnt['c'] - cnt['b']) > 1 || abs(cnt['a'] - cnt['c']) > 1) {
        return "NO";
    }

    return "YES";
}

string generateInput() {
    string s;
    for (int i = 0; i < 1000000; i++) {
        s += 'a';
        s += 'b';
        s += 'c';
    }
    return s;
}