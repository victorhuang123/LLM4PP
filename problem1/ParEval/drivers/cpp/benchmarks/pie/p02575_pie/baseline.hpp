#pragma once

#include <bits/stdc++.h>

#define ll long long
#define lld long double
#define MOD 1000000007
#define inf 1000000000000000000ll
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(v) v.begin(),v.end()

using namespace std;

int baseline(int h, int w, vector<pii>& v) {
    map<int,int> mp;
    for(int i=1;i<=w;i++) mp[i] = 0;

    map<int,int> mini = {{0,w}};

    int result = -1;

    for(int i=0;i<h;i++) {
        int l = v[i].f;
        int r = v[i].s;

        auto it = mp.lower_bound(l);
        int mn = inf;

        while(it!=mp.end() && it->f <= r) {
            mn = min(mn, r+1-(it->f)+(it->s));
            auto it1 = it++;
            if(mini[it1->s]==1) mini.erase(it1->s);
            else mini[it1->s]--;
            mp.erase(it1);
        }

        if(r+1<=w && mn<inf) {
            if(it!=mp.end() && it->f == r + 1) {
                if(it->s > mn) {
                    if(mini[it->s]==1) mini.erase(it->s);
                    else mini[it->s]--;
                    mini[mn]++;
                    it->s = mn;
                }
            }
            else {
                mp.insert({r+1,mn});
                mini[mn]++;
            }
        }

        if(mini.size()) result = mini.begin()->f + i + 1;
        else result = -1;
    }

    return result;
}

vector<pii> generateInput(int h, int w) {
    vector<pii> v(h);
    for(int i = 0; i < h; i++) {
        v[i] = {1, w};
    }
    return v;
}