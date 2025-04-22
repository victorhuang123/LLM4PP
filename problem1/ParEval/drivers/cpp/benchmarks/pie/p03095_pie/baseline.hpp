#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MOD 1000000007

ll baseline(int N, const string& s) {
    map<char,int> mp;
    for(int i = 0; i < N; i++){
        mp[s[i]]++;
    }
    ll ans = 1;
    for(char t = 'a'; t <= 'z'; t++){
        if(mp[t] == 0) continue;
        ans *= (mp[t]+1);
        ans %= MOD;
    }
    return ans-1;
}

string generateInput(int N) {
    string s = "abcdefghijklmnopqrstuvwxyz";
    string result;
    int repeat = N / 26;
    int remainder = N % 26;
    for (int i = 0; i < repeat; ++i) {
        result += s;
    }
    result += s.substr(0, remainder);
    return result;
}