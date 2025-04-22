#pragma once

#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

struct Mint {
    int x;
    Mint(int x = 0) : x(x) {}
    Mint operator*(const Mint& other) const { return Mint(x * other.x); }
    Mint operator-(const Mint& other) const { return Mint(x - other.x); }
    Mint operator/(const Mint& other) const { return Mint(x / other.x); }
};

struct S {
    Mint x;
    int len;
};

S op(S a, S b) { return {a.x * b.x, a.len + b.len}; }
S e() { return {Mint(1), 0}; }

struct F {
    int d;
};

S mapping(F f, S s) { return {s.x * Mint(f.d), s.len}; }
F composition(F f, F g) { return {f.d * g.d}; }
F id() { return {1}; }

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct lazy_segtree {
    int n;
    vector<S> data;
    vector<F> lazy;
    lazy_segtree(int n) : n(n), data(4 * n, e()), lazy(4 * n, id()) {}
    lazy_segtree(vector<S> v) : n(v.size()), data(4 * n, e()), lazy(4 * n, id()) {
        build(0, 0, n, v);
    }
    void build(int p, int l, int r, const vector<S>& v) {
        if (r - l == 1) {
            data[p] = v[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * p + 1, l, m, v);
        build(2 * p + 2, m, r, v);
        data[p] = op(data[2 * p + 1], data[2 * p + 2]);
    }
    void push(int p, int l, int r) {
        if (lazy[p] == id()) return;
        if (r - l > 1) {
            lazy[2 * p + 1] = composition(lazy[p], lazy[2 * p + 1]);
            lazy[2 * p + 2] = composition(lazy[p], lazy[2 * p + 2]);
        }
        data[p] = mapping(lazy[p], data[p]);
        lazy[p] = id();
    }
    void apply(int p, int l, int r, int a, int b, F f) {
        push(p, l, r);
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            lazy[p] = composition(f, lazy[p]);
            push(p, l, r);
            return;
        }
        int m = (l + r) / 2;
        apply(2 * p + 1, l, m, a, b, f);
        apply(2 * p + 2, m, r, a, b, f);
        data[p] = op(data[2 * p + 1], data[2 * p + 2]);
    }
    S prod(int p, int l, int r, int a, int b) {
        push(p, l, r);
        if (r <= a || b <= l) return e();
        if (a <= l && r <= b) return data[p];
        int m = (l + r) / 2;
        return op(prod(2 * p + 1, l, m, a, b), prod(2 * p + 2, m, r, a, b));
    }
    void apply(int l, int r, F f) { apply(0, 0, n, l, r, f); }
    S prod(int l, int r) { return prod(0, 0, n, l, r); }
};

vector<tuple<int, int, int>> generate_input(int n, int q) {
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < q; i++) {
        int l = rand() % n + 1;
        int r = rand() % n + 1;
        if (l > r) swap(l, r);
        int d = rand() % 9 + 1;
        queries.push_back({l, r, d});
    }
    return queries;
}

int baseline(int n, int q, vector<tuple<int, int, int>>& queries) {
    vector<Mint> poww(n + 10), calc(n + 10);
    poww[0] = 1, calc[0] = 1;
    for (int i = 1; i < n + 10; i++) {
        poww[i] = poww[i - 1] * 10;
        calc[i] = (poww[i] - 1) / 9;
    }
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(vector<S>(n + 10, {Mint(1), 1}));
    for (auto& query : queries) {
        int l, r, d;
        tie(l, r, d) = query;
        l--;
        seg.apply(l, r, {d});
    }
    return seg.prod(0, n).x.x;
}