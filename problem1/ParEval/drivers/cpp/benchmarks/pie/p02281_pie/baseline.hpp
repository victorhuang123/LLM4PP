#pragma once

#include<vector>
#include<algorithm>

using namespace std;

struct Node {
    int a;
    int b;
    int c;
};

vector<int> baseline(int n, const vector<Node>& nodes) {
    vector<int> result;
    vector<int> f(n, 0);
    int q = 0;

    for (int i = 0; i < n; i++) {
        if (nodes[i].b == -1 && nodes[i].c == -1) {
            f[nodes[i].a] = 1;
            continue;
        }
        if (nodes[i].b >= 0)
            f[nodes[i].b] = 1;
        if (nodes[i].c >= 0)
            f[nodes[i].c] = 1;
    }

    for (int i = 0; i < n; i++)
        if (!f[i]) {
            q = i;
            break;
        }

    auto qian = [&](int x, auto&& self) -> void {
        if (x != -1)
            result.push_back(nodes[x].a);
        else
            return;
        self(nodes[x].b, self);
        self(nodes[x].c, self);
    };

    auto zhong = [&](int x, auto&& self) -> void {
        if (x != -1)
            self(nodes[x].b, self);
        else
            return;
        result.push_back(nodes[x].a);
        self(nodes[x].c, self);
    };

    auto hou = [&](int x, auto&& self) -> void {
        if (x != -1)
            self(nodes[x].b, self);
        else
            return;
        if (x != -1)
            self(nodes[x].c, self);
        else
            return;
        result.push_back(nodes[x].a);
    };

    qian(q, qian);
    zhong(q, zhong);
    hou(q, hou);

    return result;
}

vector<Node> generateInput(int n) {
    vector<Node> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes[i].a = i;
        nodes[i].b = (2 * i + 1 < n) ? 2 * i + 1 : -1;
        nodes[i].c = (2 * i + 2 < n) ? 2 * i + 2 : -1;
    }
    return nodes;
}