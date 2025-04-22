#pragma once

#include <vector>
#include <algorithm>

using namespace std;

struct binary_heap {
    int N;
    vector<int> a;
    binary_heap() : N(0), a(2000000) {}
    void push(int x) {
        a[N++] = x;
        for (int i = N - 1; i;) {
            int _i = (i - 1) / 2;
            if (a[_i] >= a[i]) break;
            swap(a[i], a[_i]);
            i = _i;
        }
    }
    int pop() {
        int x = a[0];
        swap(a[0], a[N - 1]);
        N--;
        for (int i = 0; i * 2 + 1 < N;) {
            int _i = i * 2 + 1;
            if (_i + 1 < N && a[_i] < a[_i + 1]) _i++;
            if (a[_i] <= a[i]) break;
            swap(a[i], a[_i]);
            i = _i;
        }
        return x;
    }
};

vector<int> generate_input() {
    vector<int> input;
    for (int i = 0; i < 1000000; i++) {
        input.push_back(i);
    }
    return input;
}

int baseline(const vector<int>& input) {
    binary_heap pq;
    for (int x : input) {
        pq.push(x);
    }
    int sum = 0;
    while (pq.N > 0) {
        sum += pq.pop();
    }
    return sum;
}