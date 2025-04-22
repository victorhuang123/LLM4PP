#pragma once

#include <bits/stdc++.h>

using namespace std;

#define Size(x) ((int)(x).size())
#define pb push_back
typedef long long ll;
typedef long double ld;
typedef pair<int,int>pii;
const int INF = 1e9 + 10;
const int MN = 1e5 + 10;

string baseline(int n, vector<int>& arr) {
    bool fl = false;
    if (n == 1) {
        if (arr[0] & 1) return "Second";
        else return "First";
    }
    while (1) {
        if (*min_element(arr.begin(), arr.end()) == 1) {
            ll sm = 0;
            for (int i = 0; i < n; ++i) sm += arr[i];
            if ((sm - n) % 2) {
                if (!fl) return "First";
                else return "Second";
            } else {
                if (!fl) return "Second";
                else return "First";
            }
        }
        int cnt = 0;
        for (int i = 0; i < n; ++i) if (arr[i] % 2 == 0) ++cnt;
        if (cnt & 1) {
            if (fl) return "Second";
            else return "First";
        } else if (n - cnt > 1) {
            if (fl) return "First";
            else return "Second";
        }
        if (*max_element(arr.begin(), arr.end()) == 1) {
            if (!fl) return "Second";
            else return "First";
        }
        for (int i = 0; i < n; ++i) if (arr[i] & 1) arr[i]--;
        int g = -1;
        for (int i = 0; i < n; ++i) {
            if (g == -1) g = arr[i];
            else g = __gcd(g, arr[i]);
        }
        for (int i = 0; i < n; ++i) arr[i] /= g;
        fl = !fl;
    }
}

vector<int> generateInput() {
    int n = MN;
    vector<int> arr(n, 1e9);
    return arr;
}