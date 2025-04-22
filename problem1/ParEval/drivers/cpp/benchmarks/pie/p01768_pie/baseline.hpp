#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

int baseline(int n, int m, vector<string>& ls, map<string, int>& cost, multimap<string, string>& rule) {
    set<string> his, his2;
    int flg;

    auto update = [&](string a) {
        his2.insert(a);
        auto it = rule.find(a);
        while (it != rule.end() && it->first == a) {
            if (his2.count(it->second) == 0 && cost[it->second] > cost[a]) {
                cost[it->second] = cost[a];
                update(it->second);
            }
            it++;
        }
    };

    auto mk_rule = [&](string a) -> int {
        if (his.count(a) == 0) {
            his.insert(a);
            auto it = rule.find(a);
            while (it != rule.end() && it->first == a) {
                cost[a] = min(cost[a], mk_rule(it->second));
                it++;
            }
            his2.clear();
            update(a);
        }
        return cost[a];
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += mk_rule(ls[i]);
    }
    return ans;
}

vector<string> generateInput(int n, int m) {
    vector<string> ls(n);
    for (int i = 0; i < n; i++) {
        ls[i] = "node" + to_string(i);
    }
    return ls;
}