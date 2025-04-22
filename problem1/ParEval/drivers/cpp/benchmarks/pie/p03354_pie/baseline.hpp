#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<int, int> pii;

typedef pair<double,int> pdi;

int fat(int x, vector<int>& fa) {
    if(fa[x] == x)
        return x;
    return fa[x] = fat(fa[x], fa);
}

int baseline(int n, int m, vector<int>& a, vector<int>& x, vector<int>& y) {
    vector<int> fa(n + 1);
    for(int i = 1; i <= n; i++)
        fa[i] = i;

    for(int i = 0; i < m; i++) {
        int fax = fat(x[i], fa);
        int fay = fat(y[i], fa);
        if(fax != fay)
            fa[fax] = fay;
    }

    map<int, int> mp;
    vector<set<int>> big(n + 1);
    int cnt = 0;

    for(int i = 1; i <= n; i++) {
        int f = fat(i, fa);
        if(!mp.count(f)) {
            mp.insert(pii(f, ++cnt));
        }
        int id = mp[f];
        big[id].insert(a[i]);
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int f = fat(i, fa);
        int id = mp[f];
        if(big[id].count(i))
            ans++;
    }

    return ans;
}

vector<int> generateInput(int n, int m) {
    vector<int> a(n + 1), x(m), y(m);
    for(int i = 1; i <= n; i++)
        a[i] = i;
    for(int i = 0; i < m; i++) {
        x[i] = rand() % n + 1;
        y[i] = rand() % n + 1;
    }
    return {a, x, y};
}