#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef vector<int> vi;

typedef vector<ll> vll;

#define pu push

#define pb push_back

#define mp make_pair

#define eps 1e-7

#define INF 1000000000

#define sz(x) ((int)(x).size())

#define sq(x) ((x)*(x))

#define fi first

#define sec second

#define SORT(x) sort((x).begin(),(x).end())

#define all(x) (x).begin(),(x).end()

#define rep(i,n) for(int (i)=0;(i)<(int)(n);(i)++)

#define repn(i,a,n) for(int (i)=(a);(i)<(int)(n);(i)++)

#define EQ(a,b) (abs((a)-(b))<eps)

int baseline(int N, int M, vector<int>& S, vector<int>& k, vector<vector<int>>& c) {
    int mx[10010] = {0};
    int mi[10010] = {0};

    for(int i=0;i<M;i++){
        c[i].resize(k[i]);
        for(int j=0;j<k[i];j++){
            c[i][j]--;
            mx[c[i][j]]+=S[i];
            if(k[i]==1)mi[c[i][j]]+=S[i];
        }
    }

    multiset<int> ms;
    for(int i=0;i<N;i++)ms.insert(mx[i]);

    int ans = 0;
    for(int i=0;i<N;i++){
        multiset<int>::iterator it = ms.find(mx[i]);
        assert(it!=ms.end());
        ms.erase(it);
        ans = max(ans,(*ms.rbegin())-mi[i]);
        ms.insert(mx[i]);
    }

    return ans+1;
}

vector<int> generateS(int M) {
    vector<int> S(M);
    for(int i = 0; i < M; i++) {
        S[i] = rand() % 1000000 + 1;
    }
    return S;
}

vector<int> generateK(int M) {
    vector<int> k(M);
    for(int i = 0; i < M; i++) {
        k[i] = rand() % 10 + 1;
    }
    return k;
}

vector<vector<int>> generateC(int M, vector<int>& k, int N) {
    vector<vector<int>> c(M);
    for(int i = 0; i < M; i++) {
        c[i].resize(k[i]);
        for(int j = 0; j < k[i]; j++) {
            c[i][j] = rand() % N;
        }
    }
    return c;
}