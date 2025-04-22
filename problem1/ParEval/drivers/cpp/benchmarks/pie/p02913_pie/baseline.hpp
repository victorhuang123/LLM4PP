#pragma once

#include <string>
#include <map>
#include <vector>

using namespace std;

int baseline(const string& s, int n) {
    map<string, int> sop;
    int l = 0, r = n / 2;

    auto check = [&](int mid) {
        sop.clear();
        for (int i = 1; i <= s.size() - mid + 1; i++) {
            string op = s.substr(i - 1, mid);
            if (sop[op]) {
                if (i - sop[op] >= mid)
                    return true;
            } else {
                sop[op] = i;
            }
        }
        return false;
    };

    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}

string generateInput() {
    string s;
    for (int i = 0; i < 100000; i++) {
        s += 'a' + (i % 26);
    }
    return s;
}