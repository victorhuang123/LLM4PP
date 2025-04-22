#pragma once

#include <bits/stdc++.h>

using namespace std;

#define fix(f,n) std::fixed<<std::setprecision(n)<<f

#define fast ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

typedef long long int ll;

typedef unsigned long long int ull;

#define vi vector<int>

#define pii pair<int,int>

#define vii vector<pii>

#define max(a,b) ((a>b)?a:b)

#define min(a,b) ((a>b)?b:a)

#define max3(a,b,c) ((a>b)?(a>c)?a:c:(b>c)?b:c)

#define min3(a,b,c) ((a<b)?(a<c)?a:c:(b<c)?b:c)

#define REP(i,a,n) for(ll i=a;i<n;i++)

#define pb push_back

#define mp make_pair

ll dp[100000][13];

ll gs(int ind, int n, int sum, const string& a) {
    if(ind == n) {
        return (sum % 13 == 5 ? 1 : 0);
    }
    if(dp[ind][sum % 13] != -1) {
        return dp[ind][sum % 13] % 1000000007;
    }
    if(a[ind] != '?') {
        return dp[ind][sum % 13] = gs(ind + 1, n, ((sum * 10) + a[ind] - '0') % 13, a) % 1000000007;
    }
    ll res = 0;
    for(int i = 0; i <= 9; i++) {
        res += gs(ind + 1, n, ((sum * 10) + i) % 13, a);
        res %= 1000000007;
    }
    return dp[ind][sum % 13] = res % 1000000007;
}

ll baseline(const string& a) {
    memset(dp, -1, sizeof dp);
    return gs(0, a.length(), 0, a);
}

string generateInput() {
    string s(100000, '?');
    return s;
}