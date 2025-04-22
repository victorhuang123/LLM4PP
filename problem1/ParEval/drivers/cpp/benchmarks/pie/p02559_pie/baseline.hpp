#pragma once

#include <bits/stdc++.h>

using namespace std;

const int nax = 5e5+5;

vector<long long> st(2*nax);

long long baseline(int n, int q, vector<int>& initial_values, vector<tuple<int, int, int>>& queries) {
    for(int i = 0; i < n; i++) {
        st[i] = 0;
        st[i+n] = initial_values[i];
    }
    for(int i = n-1; i > 0; i--) st[i] = st[2*i] + st[2*i+1];

    long long result = 0;
    for(auto& query : queries) {
        int t = get<0>(query), a = get<1>(query), b = get<2>(query);
        if(!t) {
            for(st[a+=n] += b; a > 0; a >>= 1) st[a>>1] = st[a] + st[a^1];
        } else {
            long long ans = 0;
            int l = a + n, r = b + n;
            while(l < r) {
                if(l&1) ans += st[l++];
                if(r&1) ans += st[--r];
                l >>= 1, r >>= 1;
            }
            result += ans;
        }
    }
    return result;
}

vector<int> generate_input_values(int n) {
    vector<int> values(n);
    for(int i = 0; i < n; i++) {
        values[i] = rand() % 1000000;
    }
    return values;
}

vector<tuple<int, int, int>> generate_queries(int q, int n) {
    vector<tuple<int, int, int>> queries(q);
    for(int i = 0; i < q; i++) {
        int t = rand() % 2;
        int a = rand() % n;
        int b = rand() % n;
        if(a > b) swap(a, b);
        queries[i] = make_tuple(t, a, b);
    }
    return queries;
}