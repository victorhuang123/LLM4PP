#pragma once

#include<vector>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<stack>
#include<queue>
#include<map>
#include<cstring>

using namespace std;

const int MAX=1e5+10;

long long mod_exp(int b){
    long long res,t;
    res=1;
    t=2;
    while(b){
        if(b&1){
            res=res*t%1000000007;
        }
        t=t*t%1000000007;
        b>>=1;
    }
    return res;
}

long long baseline(int n, const vector<int>& a){
    vector<int> p(MAX, 0);
    for(int i=0;i<n;i++){
        p[a[i]]++;
    }
    int cnt=0;
    bool flag=true;
    for(int i=0;i<n;i++){
        if((n+a[i]+1)%2!=0||(n-a[i]+1)%2!=0||(p[0]!=1&&n%2==1)||(p[a[i]]!=2&&a[i]!=0)){
            flag=false;
            break;
        }
        if(p[i]==2)
        cnt++;
    }
    if(flag)
    return mod_exp(cnt);
    else
    return 0;
}

vector<int> generate_input(int n){
    vector<int> a(n);
    for(int i=0;i<n;i++){
        a[i]=i%2==0?i/2:0;
    }
    return a;
}