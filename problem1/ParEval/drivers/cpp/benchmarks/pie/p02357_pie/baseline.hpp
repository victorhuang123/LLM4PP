#pragma once

#include <deque>
#include <vector>

using namespace std;

vector<int> baseline(const vector<int>& A, int L) {
    deque<int> q;
    vector<int> result;
    int n = A.size();
    int f = 0, b = 0;
    for (; f < L - 1; ++f) {
        while (!q.empty() and A[f] < q.back())
            q.pop_back();
        q.push_back(A[f]);
    }
    for (; f < n; ++f, ++b) {
        while (!q.empty() and A[f] < q.back())
            q.pop_back();
        q.push_back(A[f]);
        result.push_back(q.front());
        if (A[b] == q.front())
            q.pop_front();
    }
    return result;
}

vector<int> generateInput(int n) {
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        A[i] = i + 1;
    }
    return A;
}