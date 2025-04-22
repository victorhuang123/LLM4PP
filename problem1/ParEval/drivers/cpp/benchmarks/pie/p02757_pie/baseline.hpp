#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll baseline(int N, int P, const string& s) {
    if (P == 2) {
        ll kotae = 0;
        for (int i = 0; i < N; i++) {
            if((s[i] - '0') % 2 == 0) kotae += i + 1;
        }
        return kotae;
    }
    if (P == 5) {
        ll kotae = 0;
        for (int i = 0; i < N; i++) {
            if ((s[i] - '0') % 5 == 0) kotae += i + 1;
        }
        return kotae;
    }

    map<int, int> MP;
    MP[0] = 1;
    ll kotae = 0;
    int ima = 1;
    int mae = 0;
    for (int i = 0; i < N; i++) {
        int a = s[N - 1 - i] - '0';
        a = (a * ima + mae) % P;
        kotae += MP[a];
        MP[a]++;
        mae = a;
        ima = ima * 10 % P;
    }
    return kotae;
}

string generateInput(int N) {
    string s(N, '0');
    for (int i = 0; i < N; i++) {
        s[i] = '0' + rand() % 10;
    }
    return s;
}