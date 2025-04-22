#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<int, int> pii;

typedef pair<double,int> pdi;

vector<string> generateInput() {
    string a;
    for (int i = 0; i < 50000; ++i) {
        a += 'a' + (i % 26);
    }
    int k = 1000000;
    return {a, to_string(k)};
}

string baseline(const string& a, int k) {
    vector<string> str;
    int cnt = 0;
    int siz = a.size();
    int mini;
    for(int i = 0; i < siz; i++) {
        str.push_back(string(1, a[i]));
        cnt++;
        mini = min(k, siz - i);
        for(int j = 1 + i; j < mini + i; j++) {
            str.push_back(str[cnt - 1] + a[j]);
            cnt++;
        }
    }
    sort(str.begin(), str.end());
    auto last = unique(str.begin(), str.end());
    str.erase(last, str.end());
    return str[k - 1];
}