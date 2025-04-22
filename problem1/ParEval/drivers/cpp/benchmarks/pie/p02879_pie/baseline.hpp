#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2e5+10 , OO = 0x3f3f3f3f;

#define clr(arr,val) memset(arr , val , sizeof (arr))
#define loop(i,n) for(int i = 0;i < int(n);i++)
#define rloop(i,n) for(int i = int(n)-1;i >= 0;i--)
#define xloop(i,a,b) for(int i = int(a);i <= int(b);i++)
#define range(n) for(int &x : n) cin >> x;
#define ALL(v) ((v).begin()) , ((v).end())
#define SZ(v)  ((int)((v).size()))
typedef pair <int,int> pii ;
typedef vector < pii > vii ;
typedef vector < int > vi;
int dx[]={1,0,-1,0};int dy[]={0,1,0,-1}; //4 Direction

int baseline(int rkm1, int rkm2) {
    if(rkm1 >= 1 && rkm1 <= 9 && rkm2 >= 1 && rkm2 <= 9)
        return (rkm1 * rkm2);
    else 
        return -1;
}

vector<pair<int, int>> generateInput() {
    vector<pair<int, int>> input;
    for (int i = 1; i <= 1000000; ++i) {
        input.push_back({i % 10, (i + 1) % 10});
    }
    return input;
}