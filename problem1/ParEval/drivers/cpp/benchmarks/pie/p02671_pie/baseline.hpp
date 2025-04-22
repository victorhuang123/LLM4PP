#pragma once

#include<bits/stdc++.h>

using namespace std;

#define rep(i,N) for(int i=0;i<(int)N;i++)

static inline int Pow(int a,int b){return b?Pow(a*a,b>>1)*(b&1?a:1):1;}

string reduce(string T)
{
    string res="";
    for(auto ch:T){if(res.size()&&res.back()=='S'&&ch=='S')res.pop_back();else res+=ch;}
    return res;
}

vector<int> baseline(int N, string T)
{
    vector<int> ans(Pow(3, N), 0);
    function<void(int, string, int, int)> solve = [&](int m, string T, int i, int p)
    {
        if(m==N){ans[i]=p;return;}
        rep(d,3)
        {
            string nextT="";int x=d;
            for(auto ch:T){if(ch=='S'){x=(3-x)%3;nextT+='S';}else{x=(x+1)%3;if(x==0)nextT+='R';}}
            solve(m+1,reduce(nextT),i+d*Pow(3,m),p+x*Pow(3,m));
        }
    };
    solve(0,reduce(T),0,0);
    return ans;
}

vector<int> generateInput(int N)
{
    string T = "SR";
    for(int i = 0; i < N; ++i) T += T;
    return baseline(N, T);
}