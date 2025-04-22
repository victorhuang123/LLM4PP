#pragma once

#include<bits/stdc++.h>

#define ll(x) (x << 1)
#define rr(x) (x << 1 | 1)

using namespace std;

const int N = 2e5+5;
const int inf = 0x3f3f3f3f;

struct SegmentTree{ int l, r, mx, tag; }t[N*4];

void up(int x){ t[x].mx = max(t[ll(x)].mx, t[rr(x)].mx); }

void build(int l, int r, int x = 1){
    t[x].l = l, t[x].r = r; int mid = (l+r>>1);
    if(l == r){ t[x].mx = -r-1; return; }
    build(l, mid, ll(x)), build(mid+1, r, rr(x)), up(x);
}

void pushdown(int x){
    if(!t[x].tag) return;
    t[ll(x)].tag += t[x].tag, t[ll(x)].mx += t[x].tag;
    t[rr(x)].tag += t[x].tag, t[rr(x)].mx += t[x].tag;
    t[x].tag = 0;
}

void update(int l, int r, int val, int x = 1){
    if(l <= t[x].l && t[x].r <= r){
        t[x].tag += val, t[x].mx += val; return;
    }
    int mid = (t[x].l+t[x].r>>1); pushdown(x);
    if(l <= mid) update(l, r, val, ll(x));
    if(mid < r) update(l, r, val, rr(x)); up(x);
}

int query(int l, int r, int x = 1){
    if(l <= t[x].l && t[x].r <= r) return t[x].mx;
    if(r < t[x].l || t[x].r < l) return -inf;
    pushdown(x);
    return max(query(l, r, ll(x)), query(l, r, rr(x)));
}

int baseline(int n, int m, vector<pair<int, int>>& edges) {
    vector<int> a[N];
    int ans = max(0, n - m);

    for (auto& edge : edges) {
        int x = edge.first, y = edge.second;
        a[x].push_back(y);
    }

    build(0, m+1);

    for(int i = 0; i <= m-1; i++){
        for(int j = 0; j < a[i].size(); j++) update(1, a[i][j], 1);
        ans = max(ans, query(i+2, m+1)-i);
    }

    return ans;
}

vector<pair<int, int>> generate_input(int n, int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int x = rand() % n;
        int y = rand() % n;
        edges.push_back({x, y});
    }
    return edges;
}