#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

int baseline(int N, vector<int>& heights) {
    int kotae = 0;
    int kari = 0;
    int mae = 0;
    rep(i, N) {
        int h = heights[i];
        if (mae >= h) kari++;
        else kari = 0;

        kotae = max(kotae, kari);
        mae = h;
    }
    return kotae;
}

vector<int> generateInput(int N) {
    vector<int> heights(N);
    rep(i, N) {
        heights[i] = rand() % 1000000 + 1;
    }
    return heights;
}