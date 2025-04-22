#pragma once

#include <vector>
#include <string>
using namespace std;

string baseline(const string& s) {
    int len = s.length(), cnt = 0, l = 0, r = 2;
    vector<bool> book(len, false);
    for (int i = 1; i < len - 1; ++i) {
        if (book[i]) continue;
        while (l && book[l]) l--;
        while (r <= i || (r < len && book[r])) r++;
        if (s[l] != s[r]) {
            cnt++;
            book[i] = true;
            i -= 2;
        }
    }
    return (cnt % 2) ? "First" : "Second";
}

string generateInput() {
    string s;
    for (int i = 0; i < 150000; ++i) {
        s += "ab";
    }
    return s;
}