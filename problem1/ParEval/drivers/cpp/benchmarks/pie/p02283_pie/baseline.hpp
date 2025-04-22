#pragma once

#include <vector>
#include <string>

struct node {
    int data;
    node* lchild;
    node* rchild;
};

typedef node* tree;

void in(tree &bt, int n) {
    if (bt) {
        if (n < bt->data)
            in(bt->lchild, n);
        else if (n > bt->data)
            in(bt->rchild, n);
    } else {
        bt = new node;
        bt->data = n;
        bt->lchild = NULL;
        bt->rchild = NULL;
    }
}

std::vector<int> out1(tree bt) {
    std::vector<int> result;
    if (bt) {
        auto left = out1(bt->lchild);
        result.insert(result.end(), left.begin(), left.end());
        result.push_back(bt->data);
        auto right = out1(bt->rchild);
        result.insert(result.end(), right.begin(), right.end());
    }
    return result;
}

std::vector<int> out2(tree bt) {
    std::vector<int> result;
    if (bt) {
        result.push_back(bt->data);
        auto left = out2(bt->lchild);
        result.insert(result.end(), left.begin(), left.end());
        auto right = out2(bt->rchild);
        result.insert(result.end(), right.begin(), right.end());
    }
    return result;
}

std::vector<std::vector<int>> baseline(int m, const std::vector<std::string>& zl, const std::vector<int>& num) {
    tree root = NULL;
    std::vector<std::vector<int>> result;
    for (int i = 0; i < m; i++) {
        if (zl[i] == "insert") {
            in(root, num[i]);
        } else if (zl[i] == "print") {
            result.push_back(out1(root));
            result.push_back(out2(root));
        }
    }
    return result;
}

std::pair<std::vector<std::string>, std::vector<int>> generate_input() {
    std::vector<std::string> zl = {"insert", "insert", "insert", "print", "insert", "print"};
    std::vector<int> num = {5, 3, 7, 0, 2, 0};
    return {zl, num};
}