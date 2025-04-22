#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#define fr(i,b,e) for(int i=(b); i<(e); ++i)
#define rp(i,e) for(int i=0; i<(e); ++i)
#define all(x) (x).begin(),(x).end()

using namespace std;
typedef long int li;
typedef long long ll;
const int INF=1000000;

vector<int> generateInput(int n) {
    vector<int> a(n);
    rp(i, n) {
        a[i] = (i % 1000000) + 1;
    }
    return a;
}

vector<ll> baseline(int n, const vector<int>& a) {
    vector<ll> cnt(1e6, 0);

    rp(i, n) {
        ++cnt[a[i]-1];
    }

    ll sum = 0;
    rp(i, n) {
        sum += cnt[i] * (cnt[i] - 1);
    }

    sum = sum >> 1;

    vector<ll> result(n);
    rp(i, n) {
        result[i] = sum - cnt[a[i]-1] + 1];
    }

    return result;
}