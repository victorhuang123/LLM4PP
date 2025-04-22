#pragma once

#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int>> involve;

vector<int> dfs2(const int now, vector<bool>& used) {
    if (used[now]) return vector<int>(0);
    else {
        used[now] = true;
    }
    vector<int> ans;
    for (auto i : involve[now]) {
        if (involve[i].size()) {
            vector<int> a(dfs2(i, used));
            ans.insert(ans.end(), a.begin(), a.end());
        }
        else {
            ans.push_back(i);
        }
    }
    return ans;
}

int baseline(int N, vector<string>& inputs) {
    int num = 0;
    map<string, int> mp;
    set<int> ed;
    involve.clear();
    involve.resize(100000);

    for (int i = 0; i < N; ++i) {
        string st = inputs[i];
        string groupname;
        vector<string> membername;
        int pre;

        for (int j = 0; j < st.size(); ++j) {
            if (st[j] == ':') {
                groupname = st.substr(0, j);
                pre = j;
            }
            else if (st[j] == ',' || st[j] == '.') {
                membername.push_back(st.substr(pre + 1, j - pre - 1));
                pre = j;
            }
        }

        if (!mp.count(groupname)) {
            mp[groupname] = num++;
        }

        for (int i = 0; i < membername.size(); ++i) {
            if (!(mp.count(membername[i]))) {
                mp[membername[i]] = num++;
            }
        }

        for (int i = 0; i < membername.size(); ++i) {
            involve[mp[groupname]].push_back(mp[membername[i]]);
            ed.emplace(mp[membername[i]]);
        }
    }

    vector<bool> used(100001, false);
    vector<int> allnames(dfs2(0, used));
    sort(allnames.begin(), allnames.end());
    const int ans(unique(allnames.begin(), allnames.end()) - allnames.begin());
    return ans;
}

vector<string> generateInput() {
    vector<string> inputs;
    for (int i = 0; i < 100000; ++i) {
        string group = "group" + to_string(i);
        string member1 = "member" + to_string(i * 2);
        string member2 = "member" + to_string(i * 2 + 1);
        inputs.push_back(group + ":" + member1 + "," + member2 + ".");
    }
    return inputs;
}