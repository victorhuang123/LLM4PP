#pragma once

#include <bits/stdc++.h>

using namespace std;

string generateInput() {
    return string(1000000, 'C') + string(1000000, 'F');
}

bool baseline(const string& st) {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    bool c = false, f = false;
    int len = st.length();

    for (int i = 0; i < len; i++) {
        if (st[i] == 'C') c = true;
        if (c && st[i] == 'F') f = true;
        if (c && f) {
            return true;
        }
    }
    return false;
}