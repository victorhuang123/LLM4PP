#pragma once

#include<vector>
#include<set>

int baseline(int D, const std::vector<int>& c, const std::vector<std::vector<int>>& S, std::vector<int>& t, int M, const std::vector<std::vector<int>>& queries) {
    std::vector<std::set<int>> id(26);
    for(int i = 0; i < 26; i++) {
        id[i].insert(-1);
    }
    int ans = 0;
    for(int i = 0; i < D; i++) {
        t[i]--;
        ans += S[i][t[i]];
        id[t[i]].insert(i);
        for(int j = 0; j < 26; j++) ans -= c[j] * (i - *id[j].rbegin());
    }
    for(int i = 0; i < 26; i++) id[i].insert(D);
    for(int i = 0; i < M; i++) {
        int d = queries[i][0], q = queries[i][1];
        d--, q--;
        ans -= S[d][t[d]];
        ans += S[d][q];
        auto it = id[t[d]].lower_bound(d);
        it = id[t[d]].erase(it);
        {
            int r = *it;
            int l = *--it;
            ans -= c[t[d]] * (r - d) * (d - l);
        }
        it = id[q].lower_bound(d);
        {
            int r = *it;
            int l = *--it;
            ans += c[q] * (r - d) * (d - l);
        }
        it++;
        id[q].insert(it, d);
        t[d] = q;
    }
    return ans;
}

std::vector<std::vector<int>> generateInput(int D, int M) {
    std::vector<std::vector<int>> S(D, std::vector<int>(26));
    std::vector<int> c(26);
    std::vector<int> t(D);
    std::vector<std::vector<int>> queries(M, std::vector<int>(2));
    for(int i = 0; i < D; i++) {
        for(int j = 0; j < 26; j++) {
            S[i][j] = rand() % 1000;
        }
        t[i] = rand() % 26;
    }
    for(int i = 0; i < 26; i++) {
        c[i] = rand() % 1000;
    }
    for(int i = 0; i < M; i++) {
        queries[i][0] = rand() % D + 1;
        queries[i][1] = rand() % 26 + 1;
    }
    return {S, c, t, queries};
}