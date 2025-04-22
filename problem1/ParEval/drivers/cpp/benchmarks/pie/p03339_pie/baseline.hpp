#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int n, const vector<char>& str) {
    vector<int> l(n, 0);
    vector<int> r(n, 0);
    int maxx = 0;

    for(int i = 0; i < n; i++) {
        if(i > 0) l[i] = l[i - 1];
        if(str[i] == 'E') {
            l[i]++;
        }
    }

    for(int i = n - 1; i >= 0; i--) {
        if(i < n - 1) r[i] = r[i + 1];
        if(str[i] == 'W') {
            r[i]++;
        }
    }

    for(int i = 0; i < n; i++) {
        r[i] = r[i] + l[i];
        maxx = max(r[i], maxx);
    }

    return n - maxx;
}

vector<char> generateInput(int n) {
    vector<char> str(n);
    for(int i = 0; i < n; i++) {
        str[i] = (i % 2 == 0) ? 'E' : 'W';
    }
    return str;
}