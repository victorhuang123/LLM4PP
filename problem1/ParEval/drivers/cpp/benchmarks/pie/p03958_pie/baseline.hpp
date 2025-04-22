#pragma once

#include <queue>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

int baseline(int K, int T, const vector<int>& a) {
    priority_queue<PII> q;
    int pre_t;
    PII p0, p1;

    for (int i = 0; i < T; i++) {
        q.push(make_pair(a[i], i));
    }

    pre_t = -1;
    while (q.size() > 1) {
        p0 = q.top(); q.pop();
        p1 = q.top(); q.pop();
        if (pre_t == p0.second) {
            p1.first--;
            pre_t = p1.second;
        } else {
            p0.first--;
            pre_t = p0.second;
        }
        if (p0.first > 0) {
            q.push(p0);
        }
        if (p1.first > 0) {
            q.push(p1);
        }
    }

    return q.top().first - 1;
}

vector<int> generateInput(int T) {
    vector<int> a(T, 1000000); // Maximize the problem scale
    return a;
}