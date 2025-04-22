#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int n, const string& s) {
    map<char,int> m1,m2; 
    int cnt, mx = 0;

    for(int i=0;i<n;i++){
        m1.clear();
        m2.clear();
        cnt = 0;

        for(int j=0;j<=i;j++){
            m1[s[j]] = 1;
        }

        for(int j=i+1;j<n;j++){
            m2[s[j]] = 1;
        }

        for(int i=0;i<=25;i++){
            if(m1['a'+i] && m2['a'+i])
                cnt++;
        }

        mx = max(mx, cnt);
    }

    return mx;
}

string generateInput(int n) {
    string s(n, 'a');
    for (int i = 0; i < n; ++i) {
        s[i] = 'a' + (i % 26);
    }
    return s;
}