#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool baseline(int n, int m, vector<vector<char>>& s) {
    vector<string> t(n);
    vector<int> h(n, -1);
    vector<int> l(m, -1);

    auto dfs1 = [&](auto&& self, int now, int ji) -> void {
        if(now == m) {
            return;
        }
        if(l[now] != -1) {
            self(self, now + 1, ji);
            return;
        }
        for (int i = now + 1; i < m; i++) {
            if(l[i] != -1)
                continue;
            bool can = true;
            for (int j = 0; j < n; j++)
                if(s[j][now] != s[h[j]][i])
                    can = false;
            if(!can)
                continue;
            l[now] = i;
            l[i] = now;
            self(self, now + 1, ji);
            l[now] = l[i] = -1;
        }
        if(ji) {
            bool can = true;
            for (int j = 0; j < n; j++)
                if(s[j][now] != s[h[j]][now])
                    can = false;
            if(can) {
                l[now] = now;
                self(self, now + 1, 0);
                l[now] = -1;
            }
        }
    };

    auto dfs2 = [&](auto&& self, int now, int ji) -> void {
        if(now == n) {
            dfs1(dfs1, 0, m % 2);
            return;
        }
        if(h[now] != -1) {
            self(self, now + 1, ji);
            return;
        }
        for (int i = now + 1; i < n; i++) {
            if(h[i] != -1)
                continue;
            h[now] = i;
            h[i] = now;
            self(self, now + 1, ji);
            h[now] = h[i] = -1;
        }
        if(ji) {
            h[now] = now;
            self(self, now + 1, 0);
            h[now] = -1;
        }
    };

    for (int i = 0; i < n; i++) {
        t[i] = string(s[i].begin(), s[i].end());
        sort(t[i].begin(), t[i].end());
    }
    dfs2(dfs2, 0, n % 2);
    return true;
}

vector<vector<char>> generateInput(int n, int m) {
    vector<vector<char>> s(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            s[i][j] = 'a' + (i + j) % 26;
        }
    }
    return s;
}