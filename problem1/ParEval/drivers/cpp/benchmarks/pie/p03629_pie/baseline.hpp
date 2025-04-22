#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef long double louble;

template<typename T1,typename T2> inline T1 max(T1 a,T2 b){return a<b?b:a;}
template<typename T1,typename T2> inline T1 min(T1 a,T2 b){return a<b?a:b;}

vector<char> generateInput(int n) {
    vector<char> s(n);
    for (int i = 0; i < n; ++i) {
        s[i] = 'a' + (i % 26);
    }
    return s;
}

vector<char> baseline(const vector<char>& s) {
    int n = s.size();
    const int alp = 26;
    vector<int> las(alp, n);
    vector<int> f(n + 2, INT_MAX);
    vector<int> wha(n, 0);
    vector<int> nex(n, INT_MAX);

    f[n + 1] = 0;
    for (int i = n - 1; i >= 0; --i) {
        las[s[i] - 'a'] = i;
        for (int j = 0; j < alp; ++j) {
            if (f[i] > f[las[j] + 1] + 1) {
                f[i] = f[las[j] + 1] + 1;
                wha[i] = j;
                nex[i] = las[j] + 1;
            }
        }
    }

    vector<char> result;
    int now = 0;
    while (now < n) {
        result.push_back('a' + wha[now]);
        now = nex[now];
    }
    return result;
}