#pragma once

#include<bits/stdc++.h>

#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define mt make_tuple

using namespace std;

const int N = 1e5;
int niz[N + 10];
int binNiz[N + 10];
int odnos[N + 10];
set<int> Set;
vector<int> brojevi;
int seg[15*N + 10];

void update(int t, int start, int end, int ind, int x) {
    if(start == end) {
        seg[t] += x;
        return;
    }

    int mid = (start + end) / 2;
    if(start <= ind && ind <= mid) update(2*t, start, mid, ind, x);
    else update(2*t+1, mid+1, end, ind, x);

    seg[t] = seg[2*t] + seg[2*t+1];
    return;
}

int query(int t, int start, int end, int l, int r) {
    if(end < l || start > r) return 0;

    if(start >= l && end <= r) return seg[t];

    int mid = (start + end) / 2;
    int x1 = query(2*t, start, mid, l, r);
    int x2 = query(2*t+1, mid+1, end, l, r);
    return (x1 + x2);
}

ll calc(int ind, ll n) {
    int x = brojevi[ind];
    memset(seg, 0, sizeof(seg));

    for(int i = 1; i <= n; i++) {
        if(niz[i] >= x) binNiz[i] = 1;
        else binNiz[i] = 0;
    }
    ll belo = 0;
    ll crno = 0;
    for(int i = 1; i <= n; i++) {
        if(binNiz[i] == 1) crno++;
        else belo++;
        odnos[i] = crno - belo;
        odnos[i] += N;
    }
    ll res = 0;
    update(1, 0, 2*N, N, 1);
    for(int i = 1; i <= n; i++) {
        int vr = odnos[i];
        res += query(1, 0, 2*N, 0, vr);
        update(1, 0, 2*N, vr, 1);
    }
    return res;
}

int binarna(int l, int r, ll n) {
    if(l == r) return l;
    int p = (l + r + 1) / 2;
    ll res = calc(p, n);
    ll uk = n*(n+1)/2;
    if(res >= (uk+1)/2) return binarna(p, r, n);
    return binarna(l, p - 1, n);
}

int baseline(ll n, vector<int>& input) {
    for(int i = 1; i <= n; i++) {
        niz[i] = input[i-1];
        Set.insert(niz[i]);
    }
    for(set<int>::iterator it = Set.begin(); it != Set.end(); it++)
        brojevi.pb(*it);

    return brojevi[binarna(0, brojevi.size()-1, n)];
}

vector<int> generateInput(ll n) {
    vector<int> input(n);
    for(ll i = 0; i < n; i++) {
        input[i] = rand() % N + 1;
    }
    return input;
}