#pragma once

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define vll vector<long long>

int baseline(const vll& v) {
    int cnt = 0;
    for(int i = 0; i < v.size(); i++) {
        for(int j = i + 1; j < v.size(); j++) {
            for(int k = j + 1; k < v.size(); k++) {
                if(v[i] != v[j] && v[i] != v[k] && v[j] != v[k]) {
                    if(v[i] + v[j] > v[k] && v[i] + v[k] > v[j] && v[j] + v[k] > v[i]) {
                        cnt++;
                    }
                }
            }
        }
    }
    return cnt;
}

vll generateInput() {
    vll v;
    for(ll i = 1; i <= 100000; i++) {
        v.push_back(i);
    }
    return v;
}