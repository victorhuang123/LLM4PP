#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef int ll;

const ll mod = 998244353;

struct node {
    int x, y;
};

int cmp(node a, node b) {
    return a.x - a.y > b.x - b.y;
}

bool baseline(int n, vector<string>& s) {
    ll ri = 0, le = 0;
    vector<node> a;
    for (int i = 0; i < n; i++) {
        ll l = 0, r = 0;
        for (char ch : s[i]) {
            if (ch == '(') l++;
            else if (ch == ')') {
                if (l) l--;
                else r++;
            }
        }
        if (!l && r) ri += r;
        else if (l && !r) le += l;
        else if (l && r) a.push_back({l, r});
    }
    sort(a.begin(), a.end(), cmp);
    for (node& nd : a) {
        if (le < nd.y) return false;
        le -= nd.y - nd.x;
    }
    return le == ri;
}

vector<string> generateInput(int n) {
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        s[i] = string(1000000, '(') + string(1000000, ')');
    }
    return s;
}