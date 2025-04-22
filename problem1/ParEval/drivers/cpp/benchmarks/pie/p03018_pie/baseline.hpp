#pragma once

#include<vector>
#include<string>

using namespace std;

ll baseline(const string& s) {
    ll ans = 0, count = 0;
    if (s[0] == 'A')
        count++;
    for (size_t i = 1; i < s.length(); i++) {
        if (s[i] == 'A')
            count++;
        if (s[i] == 'B') {
            if (s[i - 1] != 'A' || s[i + 1] != 'C')
                count = 0;
        }
        if (s[i] == 'C') {
            if (s[i - 1] == 'B') {
                ans += count;
            } else {
                count = 0;
            }
        }
    }
    return ans;
}

string generateInput() {
    string s(1000000, 'A');
    for (int i = 0; i < 1000000; i += 3) {
        s[i] = 'A';
        s[i + 1] = 'B';
        s[i + 2] = 'C';
    }
    return s;
}