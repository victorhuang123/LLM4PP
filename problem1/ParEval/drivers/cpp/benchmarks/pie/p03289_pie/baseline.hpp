#pragma once

#include <string>
#include <vector>

using namespace std;

string baseline(const string& s) {
    int idx = 0;
    if (s[0] != 'A') {
        return "WA";
    }
    bool ok = false;
    for (int i = 2; i < s.size() - 1; i++) {
        if (!ok && s[i] == 'C') {
            ok = true; idx = i;
        }
        else if (ok && s[i] == 'C') {
            ok = false; break;
        }
    }
    if (!ok) {
        return "WA";
    }
    for (int i = 0; i < s.size(); i++) {
        if (i == 0 || i == idx) continue;
        if (!('a' <= s[i] && s[i] <= 'z')) {
            return "WA";
        }
    }
    return "AC";
}

string generateInput() {
    string s(1000000, 'A');
    s[1] = 'a';
    s[500000] = 'C';
    for (int i = 2; i < 500000; i++) {
        s[i] = 'a' + (i % 26);
    }
    for (int i = 500001; i < 1000000; i++) {
        s[i] = 'a' + (i % 26);
    }
    return s;
}