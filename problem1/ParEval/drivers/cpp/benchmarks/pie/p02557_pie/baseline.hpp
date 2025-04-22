#pragma once

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 7;

vector<int> baseline(int n, vector<int>& a, vector<int>& b) {
    vector<int> pos[N];
    int cnt[N], res[N];
    set<int> have_a, have_b;
    set<pair<int, int>> st;

    auto get = [&](int i) {
        return (int)pos[i].size() + cnt[i];
    };

    auto pairup = [&](int i, int j) {
        res[pos[i].back()] = j;
        pos[i].pop_back();
        --cnt[j];
    };

    auto add = [&](int i) {
        if (get(i) > 0) st.insert({get(i), i});
        if (!pos[i].empty()) have_a.insert(i);
        if (cnt[i] > 0) have_b.insert(i);
    };

    auto del = [&](int i) {
        if (get(i) > 0) st.erase({get(i), i});
        if (!pos[i].empty()) have_a.erase(i);
        if (cnt[i] > 0) have_b.erase(i);
    };

    for (int i = 0; i < n; ++i) {
        pos[a[i]].push_back(i);
    }

    for (int i = 0; i < n; ++i) {
        ++cnt[b[i]];
    }

    for (int i = 0; i < N; ++i) {
        if (get(i) > n) {
            return {};
        }
        add(i);
    }

    int cur_n = n;
    while (!st.empty()) {
        int cur = st.rbegin()->second;
        del(cur);
        if (!st.empty() && st.rbegin()->first == cur_n) {
            int who = st.rbegin()->second;
            del(who);
            if (!pos[cur].empty() && cnt[who] > 0) pairup(cur, who); else pairup(who, cur);
            add(who);
        } else {
            if (!pos[cur].empty() && !have_b.empty()) {
                int who = *have_b.begin();
                del(who);
                pairup(cur, who);
                add(who);
            } else {
                int who = *have_a.begin();
                del(who);
                pairup(who, cur);
                add(who);
            }
        }
        add(cur);
        --cur_n;
    }

    vector<int> result(res, res + n);
    return result;
}

vector<int> generateInput(int n) {
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % N;
        b[i] = rand() % N;
    }
    return a, b;
}