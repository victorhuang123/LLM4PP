#pragma once

#include<vector>
#include<map>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

ll baseline(int n, int k, vi& a) {
    vi s(n+1);
    map<int,int> m;
    vi b[200200];
    
    s[0] = 0;
    int cnt = 1;
    m.clear();
    m[0] = 1;
    b[1].pb(0);
    
    for (int i = 1; i <= n; i++) {
        a[i]--;
        a[i] %= k;
        s[i] = (s[i-1] + a[i]) % k;
        if (m.find(s[i]) == m.end()) m[s[i]] = ++cnt;
        b[m[s[i]]].pb(i);
    }
    
    ll ans = 0;
    for (auto& it : m) {
        int p = it.second;
        int sz = b[p].size();
        if (sz == 1) continue;
        int i = 0, j = 1;
        while (j < sz) {
            if (b[p][j] - b[p][i] >= k) i++;
            else {
                ans += (ll)j - i;
                j++;
            }
        }
    }
    return ans;
}

vi generateInput(int n) {
    vi a(n+1);
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
    return a;
}