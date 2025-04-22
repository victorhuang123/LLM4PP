#pragma once

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define fbo find_by_order
#define ook order_of_key

typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<int> vi;
typedef long double ld;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

ll baseline(long long n, vector<ii>& x, vector<ii>& y) {
    vector<bool> marked(n, false);
    vector<vector<ii>> v(n);
    
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    
    for(ll i = 0; i < n - 1; i++) {
        v[x[i].se].pb(mp(x[i+1].fi - x[i].fi, x[i+1].se));
        v[x[i+1].se].pb(mp(x[i+1].fi - x[i].fi, x[i].se));
        v[y[i].se].pb(mp(y[i+1].fi - y[i].fi, y[i+1].se));
        v[y[i+1].se].pb(mp(y[i+1].fi - y[i].fi, y[i].se));
    }
    
    priority_queue<ii, vector<ii>, greater<ii>> q;
    ll minimumCost = 0;
    q.push(mp(0, 0));
    
    while(!q.empty()) {
        ii p = q.top();
        q.pop();
        ll k = p.se;
        if(marked[k]) continue;
        minimumCost += p.fi;
        marked[k] = true;
        for(auto& edge : v[k]) {
            ll u = edge.se;
            if(!marked[u]) {
                q.push(edge);
            }
        }
    }
    
    return minimumCost;
}

vector<ii> generateInput(long long n) {
    vector<ii> x(n), y(n);
    for(ll i = 0; i < n; i++) {
        x[i] = mp(rand() % 1000000, i);
        y[i] = mp(rand() % 1000000, i);
    }
    return {x, y};
}