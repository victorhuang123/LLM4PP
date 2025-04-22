#pragma once

#include <vector>
#include <algorithm>

using namespace std;

vector<int> generateInput(int n, int m, int q) {
    vector<int> a(q);
    for (int i = 0; i < q; i++) {
        a[i] = rand() % m + 1;
    }
    return a;
}

bool baseline(int n, int m, int q, vector<int>& a) {
    vector<int> ind(m + 1, -1);
    int c = 0;
    vector<vector<int>> v(n + 1);

    for (int i = q - 1; i >= 0; i--) {
        if (ind[a[i]] == -1) {
            ind[a[i]] = c;
            v[0].push_back(a[i]);
            c++;
        } else {
            int l = 0, r = n;
            while (r - l > 1) {
                int mid = (l + r) / 2;
                if (v[mid].size() <= ind[a[i]]) r = mid;
                else l = mid;
            }
            if (r < n && v[r].size() == ind[a[i]]) {
                v[r].push_back(a[i]);
            }
        }
    }

    for (int i = 1; i <= m; i++) if (ind[i] == -1) v[0].push_back(i);

    int mn = 0;
    for (int i = m - 1; i >= 1; i--) {
        if (v[0][i] < v[0][i - 1]) {
            mn = i;
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        if (v[i].size() < mn) {
            return false;
        }
    }

    return true;
}