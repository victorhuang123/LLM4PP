#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

vector<int> generate_input(int N) {
    vector<int> input(N);
    rep(i, N) {
        input[i] = (i % (N - 1)) + 1;
    }
    return input;
}

vector<int> baseline(int N, const vector<int>& input) {
    vector<int> kotae(N, 0);

    rep(i, N - 1) {
        int a = input[i];
        a--;
        kotae[a]++;
    }
    return kotae;
}