#pragma once

#include<vector>
#include<string>

using namespace std;

bool baseline(int n, vector<string>& words) {
    vector<bool> visit(26, false);
    vector<vector<bool>> g(26, vector<bool>(26, false));
    vector<int> pre(26, 0), suf(26, 0);

    auto dfs = [&](int v, auto&& dfs) -> bool {
        visit[v] = true;
        bool f = false;
        for (int i = 0; i < 26; i++)
            if (g[v][i]) {
                f = true;
                if (!visit[i]) dfs(i, dfs);
            }
        return f;
    };

    auto graph_num = [&]() -> int {
        int res = 0;
        for (int i = 0; i < 26; i++)
            if (!visit[i] && dfs(i, dfs)) res++;
        return res;
    };

    for (int i = 0; i < n; i++) {
        string s = words[i];
        int h = s[0] - 'a', t = s[(int)s.size() - 1] - 'a';

        pre[h]++;
        suf[t]++;
        g[h][t] = g[t][h] = true;
    }

    if (graph_num() != 1) return false;

    for (int i = 0; i < 26; i++) 
        if (pre[i] != suf[i]) return false;

    return true;
}

vector<string> generate_input() {
    vector<string> words;
    for (int i = 0; i < 100000; i++) {
        string word = "a";
        word += ('a' + (i % 26));
        words.push_back(word);
    }
    return words;
}