#pragma once

#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <iostream>
#include <cstring>
#define PB push_back
#define pii pair<int,int>
#define fir first
#define sec second
#define ll long long
#define MP make_pair
using namespace std;

template <class T>
inline void rd(T &x) {
    x=0; char c=getchar(); int f=1;
    while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
    while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}

int sgn(int x) { return x>0?1:-1; }
int Abs(int x) { return x>0?x:-x; }
char dy(int x) { return x>0?'U':'D'; }
char dx(int x) { return x>0?'R':'L'; }

vector<vector<char>> baseline(int n, vector<ll>& Xi, vector<ll>& Yi) {
    vector<vector<char>> s(n+1);
    int ty=((Xi[1]+Yi[1])%2+2)%2;
    for(int i=2;i<=n;++i) if(((Xi[i]+Yi[i])%2+2)%2!=ty) {
        return {};
    }

    if(ty==0) {
        for(int i=1;i<=n;++i) {
            if(Abs(Xi[i])>Abs(Yi[i])) {
                s[i].PB(dx(Xi[i]));
                Xi[i]-=sgn(Xi[i]);
            }
            else {
                s[i].PB(dy(Yi[i]));
                Yi[i]-=sgn(Yi[i]);
            }
        }
    }

    for(int j=30;j>=0;--j)
        for(int i=1;i<=n;++i)
            if(Abs(Xi[i])>Abs(Yi[i])) {
                s[i].PB(dx(Xi[i]));
                Xi[i]-=sgn(Xi[i])*(1ll<<j);
            }
            else {
                s[i].PB(dy(Yi[i]));
                Yi[i]-=sgn(Yi[i])*(1ll<<j);
            }

    return s;
}

vector<pair<ll, ll>> generateInput(int n) {
    vector<pair<ll, ll>> input(n+1);
    for(int i=1;i<=n;++i) {
        input[i].first = rand() % 1000000;
        input[i].second = rand() % 1000000;
    }
    return input;
}