#pragma once

#include <bits/stdc++.h>

#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 1000007
#define INF63 1061109567
#define INF127 9187201950435737471
#define UINF 18446744073709551615
#define F first
#define S second
#define ll long long
#define N 200010

using namespace std;

vector<pair<int, int>> baseline(int n, vector<int>& a, vector<int>& b) {
    int i, j, cnt = 0;
    vector<int> dxa(n), dxb(n), enr(4 * n), ext(4 * n);
    vector<pair<int, int>> result;

    for (i = 0; i < n; i++) {
        dxa[i] = a[i] ^ a[(i + 1) % n];
    }

    for (i = 0; i < n; i++) {
        dxb[i] = b[i] ^ b[(i + 1) % n];
    }

    for (i = 0; i < n; i++) {
        enr[cnt++] = dxb[i];
    }

    enr[cnt++] = -INF;

    for (i = 0; i < n; i++) {
        enr[cnt++] = dxa[i];
    }

    for (i = 0; i < n; i++) {
        enr[cnt++] = dxa[i];
    }

    fill(ext.begin(), ext.end(), 0);
    ext[0] = 3 * n + 1;
    cnt = 0;

    for (i = 1; i <= 3 * n;) {
        while (i + cnt <= 3 * n) {
            if (enr[cnt] != enr[i + cnt]) {
                break;
            }
            cnt++;
        }
        ext[i] = cnt;
        j = 1;
        if (cnt <= 0) {
            i++;
            continue;
        } else {
            while (i + j <= 3 * n) {
                if (j + ext[j] >= cnt) {
                    break;
                }
                ext[i + j] = ext[j];
                j++;
            }
        }
        i += j;
        cnt -= j;
    }

    for (i = n + 1; i < 2 * n + 1; i++) {
        if (ext[i] == n) {
            result.emplace_back(i - n - 1, a[i - n - 1] ^ b[0]);
        }
    }

    return result;
}

vector<int> generateInput(int n) {
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % MOD;
        b[i] = rand() % MOD;
    }
    return a, b;
}