#pragma once

#include<bits/stdc++.h>

using namespace std;

#define int long long

struct seg {
    int pre, suf, tot;
    seg() {
        pre = suf = tot = 0;
    }
};

seg combine(seg a, seg b) {
    seg c;
    c.pre = a.pre;
    c.suf = b.suf;
    c.tot = a.tot + b.tot + (int)(a.suf && b.pre);
    return c;
}

void build(int node, int beg, int en, const string& s, vector<seg>& tree) {
    if (beg == en) {
        if (s[beg-1] == 'A')
            tree[node].suf = 1;
        else if (s[beg-1] == 'C')
            tree[node].pre = 1;
        return;
    }
    int mid = (beg + en) / 2;
    build(2*node, beg, mid, s, tree);
    build(2*node+1, mid+1, en, s, tree);
    tree[node] = combine(tree[2*node], tree[2*node+1]);
}

seg qu(int node, int beg, int en, int l, int r, const vector<seg>& tree) {
    if (beg > en || l > en || r < beg) {
        seg null;
        return null;
    }
    if (l <= beg && en <= r)
        return tree[node];
    int mid = (beg + en) / 2;
    return combine(qu(2*node, beg, mid, l, r, tree), qu(2*node+1, mid+1, en, l, r, tree));
}

int baseline(int n, int q, const string& s, const vector<pair<int, int>>& queries) {
    vector<seg> tree(4 * n);
    build(1, 1, n, s, tree);
    int result = 0;
    for (const auto& query : queries) {
        int l = query.first;
        int r = query.second;
        result += qu(1, 1, n, l, r, tree).tot;
    }
    return result;
}

vector<pair<int, int>> generate_input(int n, int q) {
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        queries[i] = {1, n};
    }
    return queries;
}