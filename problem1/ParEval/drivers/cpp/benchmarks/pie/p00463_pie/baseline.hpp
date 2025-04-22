#pragma once

#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Side {
    int h, w, ul, ur, dl, dr;
    Side(int h = 0, int w = 0, int ul = -1, int ur = -1, int dl = -1, int dr = -1) : h(h), w(w), ul(ul), ur(ur), dl(dl), dr(dr) {}
    bool operator<(const Side &a) const { return h < a.h; }
};

int baseline(int N, int M, int H, int K, vector<int>& s, vector<int>& a, vector<int>& b) {
    vector<Side> ss(M);
    vector<int> l(N);
    map<int, int> m;

    for (int i = 0; i < N; i++) l[i] = i;

    for (int i = 0; i < M; i++) {
        ss[i] = Side(b[i], a[i] - 1);
    }

    sort(ss.begin(), ss.end());

    for (int i = 0; i < M; i++) {
        Side &sd = ss[i];
        sd.ul = l[sd.w];
        sd.ur = l[sd.w + 1];
        swap(l[sd.w], l[sd.w + 1]);
        sd.dl = l[sd.w];
        sd.dr = l[sd.w + 1];
    }

    for (int i = 0; i < N; i++) m[l[i]] = i;

    for (int i = 0; i < M; i++) {
        Side &sd = ss[i];
        sd.dl = m[sd.dl];
        sd.dr = m[sd.dr];
    }

    int sum = 0;
    for (int i = 0; i < K; i++) sum += s[m[i]];
    int res = sum;

    for (int i = 0; i < M; i++) {
        Side sd = ss[i];
        int diff = 0;
        int l = 0, r = 0;
        if (0 <= sd.ul && sd.ul < K) l = 1;
        if (0 <= sd.ur && sd.ur < K) r = 1;
        if (!l && r) diff = s[sd.dr] - s[sd.dl];
        else if (l && !r) diff = s[sd.dl] - s[sd.dr];
        res = min(res, sum + diff);
    }

    return res;
}

vector<int> generateInput(int N, int M, int H, int K) {
    vector<int> s(N), a(M), b(M);
    for (int i = 0; i < N; i++) s[i] = rand() % 1000000;
    for (int i = 0; i < M; i++) {
        a[i] = rand() % (N - 1) + 1;
        b[i] = rand() % H + 1;
    }
    return {s, a, b};
}