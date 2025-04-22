
#include<bits/stdc++.h>
using namespace std;

int baseline(int n, vector<string>& s) {
    sort(s.begin(), s.end());
    string s1 = "";
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        if(s1 != s[i]) {
            ans++;
            s1 = s[i];
        }
    }
    return ans;
}

