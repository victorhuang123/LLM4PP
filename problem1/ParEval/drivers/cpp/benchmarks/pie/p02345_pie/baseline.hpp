#pragma once

#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

#define MAX 1000001

int n, dat[MAX * 2 - 1];

void update(int i, int x) {
    i += n - 1;
    dat[i] = x;
    while(i > 0) {
        i = (i - 1)/2;
        dat[i] = min(dat[i*2+1], dat[i*2+2]);
    }
}

int query(int a, int b, int k, int l, int r) {
    if(r <= a || b <= l) return INT_MAX;
    if(a <= l && r <= b) return dat[k];
    return min(query(a, b, k*2+1, l, (l+r)/2), query(a, b, k*2+2, (l+r)/2, r));
}

vector<int> baseline(int N, int q, vector<vector<int>>& operations) {
    vector<int> results;
    for(int i = 0; i < MAX * 2 - 1; i++) dat[i] = INT_MAX;
    n = 1;
    while(n < N) n *= 2;
    for(auto& op : operations) {
        int a = op[0], b = op[1], c = op[2];
        if(!a) update(b, c);
        else results.push_back(query(b, c+1, 0, 0, n));
    }
    return results;
}

vector<vector<int>> generateInput(int N, int q) {
    vector<vector<int>> operations(q);
    for(int i = 0; i < q; i++) {
        if(i % 2 == 0) {
            operations[i] = {0, rand() % N, rand() % 100};
        } else {
            int left = rand() % N;
            int right = left + rand() % (N - left);
            operations[i] = {1, left, right};
        }
    }
    return operations;
}