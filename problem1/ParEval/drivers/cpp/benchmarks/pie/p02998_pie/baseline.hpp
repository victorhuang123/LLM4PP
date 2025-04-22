#pragma once

#include<bits/stdc++.h>

using namespace std;

#define reg register

#define MaxN 100003

#define hhhhhhh 1000000

int Find(int fa[], int d) {
    if(fa[d] == d) return d;
    else return fa[d] = Find(fa, fa[d]);
}

long long baseline(int N, vector<pair<int, int>>& points) {
    int fa[MaxN];
    long long ans = 0, cnty[MaxN] = {0}, cntx[MaxN] = {0};
    map<int, bool> bk[MaxN];
    struct Nd {
        int x, y;
    } a[MaxN];

    for(reg int i = 1; i <= 100000; ++i)
        fa[i] = i;

    for(reg int i = 1; i <= N; ++i)
        a[i].x = points[i-1].first, a[i].y = points[i-1].second;

    sort(a + 1, a + 1 + N, [](Nd aa, Nd bb) {
        return aa.x < bb.x;
    });

    for(reg int i = 1; i < N; ++i)
        if(a[i].x == a[i + 1].x)
            fa[Find(fa, a[i].y)] = Find(fa, a[i + 1].y);

    for(reg int i = 1; i <= 100000; ++i)
        ++cnty[Find(fa, i)];

    for(reg int i = 1; i <= N; ++i)
        if(!bk[Find(fa, a[i].y)][a[i].x]) {
            ++cntx[Find(fa, a[i].y)];
            bk[Find(fa, a[i].y)][a[i].x] = true;
        }

    for(reg int i = 1; i <= 100000; ++i)
        ans += cnty[i] * cntx[i];

    return ans - N;
}

vector<pair<int, int>> generateInput() {
    vector<pair<int, int>> points;
    for (int i = 1; i <= 100000; ++i) {
        points.push_back({i, i});
    }
    return points;
}