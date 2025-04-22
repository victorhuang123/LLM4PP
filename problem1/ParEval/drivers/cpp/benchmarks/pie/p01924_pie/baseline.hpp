#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef vector<int> vi;

typedef vector<ll> vll;

#define pu push

#define pb push_back

#define mp make_pair

#define eps 1e-7

#define INF 1000000000

#define sz(x) ((int)(x).size())

#define sq(x) ((x)*(x))

#define fi first

#define sec second

#define SORT(x) sort((x).begin(),(x).end())

#define all(x) (x).begin(),(x).end()

#define rep(i,n) for(int (i)=0;(i)<(int)(n);(i)++)

#define repn(i,a,n) for(int (i)=(a);(i)<(int)(n);(i)++)

#define EQ(a,b) (abs((a)-(b))<eps)

int baseline(int T, int D, int L, vector<int>& x) {
    if (T + D + L == 0) return 1;

    vector<int> rui(200100);

    for (int i = 0; i < T; i++) {
        if (x[i] >= L) {
            rui[i]++;
            rui[i + D]--;
        }
    }

    for (int i = 1; i < 200100; i++) rui[i] += rui[i - 1];

    int ans = 0;
    for (int i = 0; i < T - 1; i++) if (rui[i]) ans++;

    return ans;
}

vector<int> generateInput(int T) {
    vector<int> x(T);
    for (int i = 0; i < T; i++) {
        x[i] = rand() % 1000000 + 1;
    }
    return x;
}