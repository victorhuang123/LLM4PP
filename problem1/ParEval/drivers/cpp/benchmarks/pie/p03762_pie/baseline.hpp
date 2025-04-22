#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> P;
typedef long long ll;
typedef long double ld;

const int inf=1e9+7;
const ll longinf=1LL<<60;
const int mx=100010;
const ll mod=1e9+7;

vector<int> generate_input() {
    vector<int> input(mx);
    for (int i = 0; i < mx; ++i) {
        input[i] = i;
    }
    return input;
}

ll baseline(const vector<int>& input) {
    ll result = 0;
    for (int i = 0; i < input.size(); ++i) {
        result += input[i];
    }
    return result;
}