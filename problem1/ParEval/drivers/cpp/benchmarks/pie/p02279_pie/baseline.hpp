#pragma once

#include <vector>
#include <string>

using namespace std;

typedef long long int llint;

struct Node {
    llint parent;
    llint depth;
    string state;
    vector<llint> children;
    Node():parent(-1),depth(0){}
};

void set_depth(vector<Node> &Nodes, Node &node, int depth) {
    node.depth = depth;
    for (int i = 0; i < node.children.size(); i++) {
        set_depth(Nodes, Nodes[node.children[i]], depth + 1);
    }
}

vector<Node> baseline(llint n, const vector<pair<llint, vector<llint>>>& input) {
    llint const N_MAX = 100000;
    vector<Node> Nodes(N_MAX);

    for (llint i = 0; i < n; i++) {
        llint id = input[i].first;
        const vector<llint>& children = input[i].second;
        Node &x = Nodes[id];
        for (llint j = 0; j < children.size(); j++) {
            llint c = children[j];
            x.children.push_back(c);
            Nodes[c].parent = id;
        }
    }

    Node root;
    for (llint i = 0; i < n; i++) {
        Node &x = Nodes[i];
        if (x.parent == -1) {
            x.state = "root";
            root = x;
        }
        else if (x.children.size() == 0) {
            x.state = "leaf";
        }
        else {
            x.state = "internal node";
        }
    }

    set_depth(Nodes, root, 0);

    return Nodes;
}

vector<pair<llint, vector<llint>>> generate_input(llint n) {
    vector<pair<llint, vector<llint>>> input(n);
    for (llint i = 0; i < n; i++) {
        input[i].first = i;
        for (llint j = 0; j < 10; j++) {
            input[i].second.push_back((i * 10) + j);
        }
    }
    return input;
}