#pragma once

#include<vector>
#include<algorithm>

using namespace std;

bool baseline(int n, const vector<int>& a) {
    int l = a[0], r = a[0];
    for(int i = 1 ; i < n ; i++) {
        l = min(a[i], l);
        r = max(a[i], r);
    }
    if(r - l > 1) return false;
    else {
        if(l == r) {
            int gg = n - l;
            if(gg == 1) return true;
            else {
                if(n == 1 || gg >= l) return true;
                else return false;
            }
        } else {
            int cnt1 = 0, cnt2 = 0;
            for(int i = 0 ; i < n ; i++) {
                if(a[i] == l) cnt1++;
                if(a[i] == r) cnt2++;
            }
            if(cnt1 >= r) return false;
            else {
                int gg = n - r;
                if(gg >= r - cnt1) return true;
                else return false;
            }
        }
    }
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        a[i] = rand() % 100000 + 1;
    }
    return a;
}