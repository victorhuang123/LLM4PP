#pragma once

#include<bits/stdc++.h>

#define ll long long int

using namespace std;

vector<string> generateInput(ll h, ll w) {
    vector<string> ss(h);
    for (ll i = 0; i < h; i++) {
        ss[i] = string(w, '.');
    }
    return ss;
}

vector<string> baseline(ll h, ll w, vector<string> ss) {
    string x(w + 2, '#');
    vector<string> result;
    result.push_back(x);
    for (ll i = 0; i < h; i++) {
        result.push_back("#" + ss[i] + "#");
    }
    result.push_back(x);
    return result;
}