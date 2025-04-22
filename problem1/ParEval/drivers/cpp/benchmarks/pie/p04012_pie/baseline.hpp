

#include <bits/stdc++.h>
using namespace std;

bool baseline(const string& s) {
    vector<int> v(26, 0);
    for (char c : s) {
        ++v[c - 'a'];
    }
    for (int cnt : v) {
        if (cnt & 1) {
            return false;
        }
    }
    return true;
}

