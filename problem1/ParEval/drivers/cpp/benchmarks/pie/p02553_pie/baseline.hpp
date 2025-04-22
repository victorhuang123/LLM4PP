#pragma once

#include<bits/stdc++.h>

using namespace std;

#define Ff(i,a,n) for(i=a;i<n;i++)
#define Fr(i,a,n) for(i=a;i>n;i--)
#define ll long long
#define FAST ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for(auto it = a.begin(); it != a.end(); it++)

typedef pair<ll, ll>	pa;
typedef vector<ll>		vc;
typedef vector<pa>		vp;
typedef vector<vc>		vvc;

const int mod = 1000000007;
const int N = 3e5, M = N;

ll baseline(const vc& a) {
    ll maxi = -1e18;
    Ff(i, 0, 2) {
        Ff(j, 2, a.size()) {
            maxi = max(maxi, a[i] * a[j]);
        }
    }
    return maxi;
}

vc generateInput() {
    vc a(N);
    Ff(i, 0, N) {
        a[i] = rand() % mod;
    }
    return a;
}