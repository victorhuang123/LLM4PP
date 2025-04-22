#pragma once

#include <vector>
#include <algorithm>
using namespace std;

int baseline(int n, const vector<int>& a) {
    vector<int> ls(n + 1), num(n + 1), pos(n + 1);
    vector<int> sum(4 * n + 5, 0);

    auto add = [&](int now, int l, int r, int pos) {
        sum[now]++;
        if (l == r) return;
        int mid = l + r >> 1;
        if (pos <= mid) add(now * 2, l, mid, pos);
        else add(now * 2 + 1, mid + 1, r, pos);
    };

    auto ask = [&](int now, int l, int r, int L, int R) {
        if (l > R || L > r) return false;
        if (L <= l && r <= R) return (sum[now] != 0);
        int mid = l + r >> 1;
        return ask(now * 2, l, mid, L, R) | ask(now * 2 + 1, mid + 1, r, L, R);
    };

    auto find = [&](int x, int right) {
        int l = 1, r = n;
        for (int mid = l + r >> 1; l < r; mid = l + r >> 1) {
            if (ls[mid] < x) l = mid + 1;
            else r = mid;
        }
        while (ls[l] > x && l > 0) l--;
        if (l == 0) return false;
        return ask(1, 1, n, 1, l);
    };

    auto check = [&](int x) {
        fill(sum.begin(), sum.end(), 0);
        for (int i = 1; i <= n; i++) {
            if (find(a[i] - x, i)) return true;
            add(1, 1, n, num[i]);
        }
        return false;
    };

    int minn = 0, maxn = 0;
    for (int i = 1; i <= n; i++) {
        ls[i] = a[i];
        maxn = max(maxn, a[i]);
    }
    sort(ls.begin() + 1, ls.begin() + n + 1);
    for (int i = 1; i <= n; i++) {
        num[i] = lower_bound(ls.begin() + 1, ls.begin() + n + 1, a[i]) - ls.begin();
        pos[num[i]] = i;
    }
    int l = minn, r = maxn;
    for (int mid = (l + r) >> 1; l < r; mid = (l + r) >> 1) {
        if (check(mid)) l = mid + 1;
        else r = mid;
    }
    if (!check(l)) l--;
    fill(sum.begin(), sum.end(), 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (find(a[i] - l, i)) ans++;
        add(1, 1, n, num[i]);
    }
    return ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}