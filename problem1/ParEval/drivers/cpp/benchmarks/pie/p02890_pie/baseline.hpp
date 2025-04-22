#pragma once

#include <bits/stdc++.h>
#define int long long
#define inf 1000000007
#define pa pair<int,int>
#define ll long long
#define pal pair<double,double>
#define ppap pair<pa,int>
#define PI 3.14159265358979323846
#define paa pair<int,char>
#define mp make_pair
#define pb push_back
#define EPS (1e-8)

using namespace std;

vector<int> baseline(int n, vector<int>& input) {
    int cnt[320000] = {};
    int imo[400020] = {};

    for (int i = 0; i < n; i++) {
        cnt[input[i]]++;
    }

    vector<int> ve;
    for (int i = 1; i <= n; i++) if (cnt[i]) ve.pb(cnt[i]);

    for (auto v : ve) {
        imo[1] += 1;
        imo[v] -= 1;
    }

    for (int i = 1; i <= 400020; i++) imo[i] += imo[i - 1];

    for (auto v : ve) {
        imo[v]++;
    }

    for (int i = 1; i <= 400020; i++) imo[i] += imo[i - 1];

    vector<int> result;
    for (int c = 1; c <= n; c++) {
        int si = 0, ue = n + 10, me;
        while (ue - si > 1) {
            me = (ue + si) / 2;
            if (imo[me] >= c * me) si = me;
            else ue = me;
        }
        result.pb(si);
    }
    return result;
}

vector<int> generateInput(int n) {
    vector<int> input(n);
    for (int i = 0; i < n; i++) {
        input[i] = i + 1;
    }
    return input;
}