#pragma once

#include<bits/stdc++.h>

#define ll long long

using namespace std;

#define maxn 100010

#define mod 1000000007

struct cv{
    int x,y;
};

bool cmp(cv p, cv q){
    if(p.x != q.x) return p.x < q.x;
    return p.y < q.y;
}

bool baseline(int n, vector<cv>& a, vector<int>& b){
    set<int> s[maxn];
    int dp[maxn], du[maxn];
    int cnt = 0;
    int flag = 0;

    sort(a.begin(), a.end(), cmp);
    sort(b.begin(), b.end());

    for(int i = 0; i < n; i++){
        if(a[i].x > b[i]){
            return false;
        }
        if(i < n - 1 && a[i + 1].x < b[i]) flag = 1;
        if(i != 0 && b[i] == b[i - 1]) flag = 1;
        if(i != 0 && a[i].x != a[i - 1].x){
            cnt++;
            s[cnt].insert(a[i].y);
        } else {
            s[cnt].insert(a[i].y);
            if(i != 0) flag = 1;
        }
    }

    if(flag){
        return true;
    }

    for(int i = 0; i < n; i++){
        dp[lower_bound(b.begin(), b.end(), a[i].y) - b.begin()] = i;
    }

    cnt = 0;
    for(int i = 0; i < n; i++){
        if(du[i]) continue;
        cnt++;
        du[i] = 1;
        int x = dp[i];
        while(du[x] == 0){
            du[x] = 1;
            x = dp[x];
        }
    }

    return cnt >= 2;
}

vector<cv> generateInput(int n){
    vector<cv> a(n);
    for(int i = 0; i < n; i++){
        a[i].x = rand() % 1000000;
        a[i].y = rand() % 1000000;
    }
    return a;
}

vector<int> generateB(int n){
    vector<int> b(n);
    for(int i = 0; i < n; i++){
        b[i] = rand() % 1000000;
    }
    return b;
}