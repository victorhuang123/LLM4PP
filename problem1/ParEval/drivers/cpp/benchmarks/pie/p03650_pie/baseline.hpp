#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> generateInput(int n) {
    vector<int> p(n + 1), in(n + 1);
    for (int i = 1; i <= n; i++) {
        p[i] = (i % n) + 1;
        in[i] = 1;
    }
    return p;
}

bool baseline(int n, vector<int> p, vector<int> in, vector<set<int>> s, vector<bool> v) {
    vector<int> x, y;
    int ta, tb;

    auto go = [&](int a) {
        v[a] = 1;
        for (int i = 0; ; i++)
            if (s[a].find(i) == s[a].end()) {
                s[p[a]].insert(i);
                break;
            }
        in[p[a]]--;
        if (in[p[a]] == 0)
            go(p[a]);
    };

    for (int i = 1; i <= n; i++)
        if (!in[i] && !v[i])
            go(i);

    for (int i = 1; i <= n; i++)
        if (!v[i]) {
            ta = i;
            while (1) {
                x.push_back(ta);
                if (p[ta] == i)
                    break;
                ta = p[ta];
            }
            break;
        }

    for (int i = 0; y.size() < 2; i++)
        if (s[x[0]].find(i) == s[x[0]].end())
            y.push_back(i);

    for (int i = 0; i < 2; i++) {
        in[0] = y[i];
        for (int j = 1; j < x.size(); j++)
            for (int k = 0; ; k++)
                if (in[j - 1] != k && s[x[j]].find(k) == s[x[j]].end()) {
                    in[j] = k;
                    break;
                }
        if (i == 0 && in[x.size() - 1] != y[0]) {
            return true;
        }
        if (i == 1 && in[x.size() - 1] == y[0]) {
            return true;
        }
    }
    return false;
}