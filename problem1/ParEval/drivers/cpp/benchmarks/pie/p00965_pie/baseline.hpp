#pragma once

#include<vector>
#include<algorithm>
using namespace std;

struct Interval {
    int x, y;
};

pair<int, int> baseline(int n, vector<Interval>& a) {
    vector<int> num(200002, 0), l(200002, 0), r(200002, 0);
    for(int i = 0; i < n; i++){
        int x = a[i].x, y = a[i].y;
        num[x]++, num[y]--;
        r[x+1]++, l[y]++;
    }
    int Max = 0, sum = 0;
    for(int i = 1; i <= 200000; i++){
        sum += num[i];
        Max = max(Max, sum);
    }
    for(int i = 2; i <= 200000; i++){
        l[i] += l[i-1], r[i] += r[i-1];
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans = max(ans, r[a[i].y] - l[a[i].x]);
    }
    return make_pair(ans, Max);
}

vector<Interval> generateInput(int n) {
    vector<Interval> a(n);
    for(int i = 0; i < n; i++) {
        a[i].x = i + 1;
        a[i].y = i + 100000;
    }
    return a;
}