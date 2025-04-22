#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> baseline(int L) {
    L--;

    vector<int> u, v, c;
    #define add(x, y, z) {u.push_back(x); v.push_back(y); c.push_back(z);}

    int i;

    for (i = 19; i > 0 && L > (1 << (19 - i)); --i) {
        add(i, i + 1, 0);
        add(i, i + 1, (1 << (19 - i)));
        L -= (1 << (19 - i));
    }

    if (i) add(i, i + 1, 0);

    int val = (1 << (19 - i));

    for (int is = 0; is <= 20; ++is) {
        if ((L >> is) & 1) {
            add(max(i, 1), 20 - is, val);
            val += (1 << is);
        }
    }

    while ((--i) > 0)
        add(i, i + 1, 0);

    vector<vector<int>> result;
    result.push_back(u);
    result.push_back(v);
    result.push_back(c);

    return result;
}

vector<int> generateInput() {
    return {100000};
}