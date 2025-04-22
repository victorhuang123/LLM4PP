#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll baseline(int n, int k, int r, int s, int p, string T) {
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        if(i >= k){
            if(T[i-k] == T[i]){
                T[i] = 'a';
            }else{
                if(T[i] == 'r') ans += p;
                if(T[i] == 's') ans += r;
                if(T[i] == 'p') ans += s;
            }
        }else{
            if(T[i] == 'r') ans += p;
            if(T[i] == 's') ans += r;
            if(T[i] == 'p') ans += s;
        }
    }
    return ans;
}

string generateInput(int n) {
    string T;
    for (int i = 0; i < n; ++i) {
        int randVal = rand() % 3;
        if (randVal == 0) T += 'r';
        else if (randVal == 1) T += 's';
        else T += 'p';
    }
    return T;
}