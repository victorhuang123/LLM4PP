#pragma once

#include <vector>
#include <cstring>

using namespace std;

#define NIL -1

int root = NIL;

void insert(int z, vector<int>& key, vector<int>& parent, vector<int>& leftc, vector<int>& rightc) {
    int x, y;
    y = NIL;
    x = root;

    while (x != NIL) {
        y = x;
        if (key[z] < key[x]) x = leftc[x];
        else x = rightc[x];
    }

    parent[z] = y;

    if (y == NIL) root = z;
    else if (key[z] < key[y]) leftc[y] = z;
    else rightc[y] = z;
}

bool find(int now, int data, vector<int>& key, vector<int>& leftc, vector<int>& rightc) {
    if (now == NIL) return false;
    if (data == key[now]) return true;
    if (data < key[now]) return find(leftc[now], data, key, leftc, rightc);
    else return find(rightc[now], data, key, leftc, rightc);
}

vector<string> baseline(int n, vector<string>& str, vector<int>& data) {
    vector<int> key(n, NIL);
    vector<int> parent(n, NIL);
    vector<int> leftc(n, NIL);
    vector<int> rightc(n, NIL);
    vector<string> result;
    int z = 0;

    for (int i = 0; i < n; i++) {
        if (str[i] == "insert") {
            key[z] = data[i];
            insert(z, key, parent, leftc, rightc);
            z++;
        } else if (str[i] == "find") {
            if (find(root, data[i], key, leftc, rightc)) {
                result.push_back("yes");
            } else {
                result.push_back("no");
            }
        }
    }

    return result;
}

vector<string> generateInput(int n) {
    vector<string> str(n);
    vector<int> data(n);

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            str[i] = "insert";
        } else {
            str[i] = "find";
        }
        data[i] = i;
    }

    return str;
}