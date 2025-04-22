#pragma once

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define f first
#define s second
#define int long long
#define double long double
typedef long long ll;
typedef pair<int,int> pii;
#define MAXN 1123456
#define INF LLONG_MAX
#define MOD 32416187567
#define cte 10002
#define MAX ULLONG_MAX

string baseline(int n, vector<pair<int,pii>>& v) {
    sort(v.begin(), v.end());

    int dis = abs(v[0].s.s) + abs(v[0].s.f);
    if (dis > v[0].f || (v[0].f - dis) % 2 == 1) {
        return "No";
    }

    for (int i = 1; i < n; i++) {
        int dis = abs(v[i].s.s - v[i-1].s.s) + abs(v[i].s.f - v[i-1].s.f);
        if (dis > v[i].f - v[i-1].f || ((v[i].f - v[i-1].f) - dis) % 2 == 1) {
            return "No";
        }
    }

    return "Yes";
}

vector<pair<int,pii>> generateInput(int n) {
    vector<pair<int,pii>> v;
    for (int i = 1; i <= n; i++) {
        v.pb(mp(i, mp(i-1, i-1)));
    }
    return v;
}