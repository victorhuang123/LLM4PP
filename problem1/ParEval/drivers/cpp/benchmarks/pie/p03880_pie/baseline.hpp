#pragma once

#include <bits/stdc++.h>

#define rep(i,n) for(int i=0;i<(n);++i)

#define ALL(A) A.begin(), A.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> P;

const int MAX_N = (int)1e5 + 5;

bool used[MAX_N];    // この数字を使ったかどうか
bool change[MAX_N];  // この桁が１引く事によって変化するかどうか
bool cand[MAX_N];    // この数字が候補である

int baseline(int N, vector<int>& a) {
    memset(used, false, sizeof(used));

    int ans = 0;
    int res = 0;
    rep (i, N) ans ^= a[i];
    if (ans == 0) {
        res = 0;
    } else {
        for(int digit = 31; digit >= 0; --digit) {
            memset(cand, false, sizeof(cand));
            memset(change, false, sizeof(change));
            int cnt = 0;
            rep (i, N) {
                if (a[i] & (1<<digit)) {
                    ++cnt;
                    if (!used[i]) cand[i] |= true;
                    if (!used[i] && !((a[i] - 1) & (1<<digit))) change[i] |= true;
                }
            }

            if (cnt % 2 == 0) {
                rep (i, N) used[i] |= change[i];
            } else {
                bool one = false;
                rep (i, N) {
                    if (!used[i] && change[i]) {
                        if (!one) {
                            --a[i];
                            ++res;
                            one |= true;
                        }
                        used[i] |= true;
                    }
                }
                if (!one) {
                    res = -1;
                    break;
                }
            }
        }
    }
    return res;
}

vector<int> generateInput(int N) {
    vector<int> a(N);
    rep(i, N) a[i] = rand() % (1 << 30);
    return a;
}