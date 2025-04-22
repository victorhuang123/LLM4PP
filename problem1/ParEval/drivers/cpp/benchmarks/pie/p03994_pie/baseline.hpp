#pragma once

#include<vector>
#include<string>
#include<algorithm>

using namespace std;

typedef long long LL;

string baseline(const string& s, LL k) {
    vector<LL> a(s.length() + 1);
    for (size_t i = 1; i <= s.length(); ++i) {
        a[i] = (LL)s[i - 1];
    }

    for (size_t i = 1; i <= s.length(); ++i) {
        if (k == 0) break;
        if (a[i] == 97) continue;
        else {
            if (a[i] + k > 122) {
                k = k - (122 - a[i] + 1);
                a[i] = 97;
            }
        }
    }

    if (k > 0) {
        if (k > 26) k %= 26;
        a[s.length()] += k;
        if (a[s.length()] > 122) {
            a[s.length()] = 97 + a[s.length()] - 122 - 1;
        }
    }

    string result;
    for (size_t i = 1; i <= s.length(); ++i) {
        result += (char)a[i];
    }

    return result;
}

string generateInput() {
    return string(1e5, 'z');
}