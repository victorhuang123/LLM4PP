#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<int> baseline(const string& q) {
    int g, nt;
    vector<int> re(q.length(), 0);

    for (g = nt = 0; q[g]; g++) {
        if (q[g] == 'R') nt++;
        else if (nt) re[g-1] = (nt + 1) / 2, re[g] = nt / 2, nt = 0;
    }

    for (g = q.length() - 1, nt = 0; g >= 0; g--) {
        if (q[g] == 'L') nt++;
        else if (nt) re[g+1] += (nt + 1) / 2, re[g] += nt / 2, nt = 0;
    }

    return re;
}

string generateInput() {
    return string(100000, 'R') + string(100000, 'L');
}