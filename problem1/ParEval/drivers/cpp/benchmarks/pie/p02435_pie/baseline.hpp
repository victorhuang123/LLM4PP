#pragma once

#include <stack>
#include <vector>
#include <tuple>

using namespace std;

vector<int> baseline(int n, int q, const vector<tuple<int, int, int>>& operations) {
    stack<int> st[1001];
    vector<int> result;

    for (const auto& op : operations) {
        int o = get<0>(op);
        int t = get<1>(op);
        int x = get<2>(op);

        if (o == 0) {
            st[t].push(x);
        } else if (o == 1) {
            if (!st[t].empty()) {
                result.push_back(st[t].top());
            }
        } else if (o == 2) {
            if (!st[t].empty()) {
                st[t].pop();
            }
        }
    }

    return result;
}