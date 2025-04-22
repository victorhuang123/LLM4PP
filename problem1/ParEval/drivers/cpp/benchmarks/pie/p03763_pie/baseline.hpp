#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<char> baseline(int n, vector<string> s) {
    int cnt[26] = {0};

    for (int i = 0; i < (int)s[0].size(); i++) {
        cnt[s[0][i] - 'a']++;
    }

    for (int i = 1; i < n; i++) {
        int curcnt[26] = {0};
        for (int j = 0; j < (int)s[i].size(); j++) {
            curcnt[s[i][j] - 'a']++;
        }
        for (int j = 0; j < 26; j++) {
            cnt[j] = min(cnt[j], curcnt[j]);
        }
    }

    vector<char> v;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            v.push_back(i + 'a');
        }
    }

    sort(v.begin(), v.end());
    return v;
}

vector<string> generateInput() {
    int n = 50;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        s[i] = string(1000, 'a' + (i % 26));
    }
    return s;
}