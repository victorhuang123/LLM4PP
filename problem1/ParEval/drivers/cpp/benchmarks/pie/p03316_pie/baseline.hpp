#pragma once

#include<bits/stdc++.h>

using namespace std;

string baseline(long long n) {
    long long cnt = 0;
    string s = to_string(n);

    for(int i = 0; i < s.size(); i++)
        cnt += (s[i] - '0');

    if(n % cnt)
        return "No";
    else
        return "Yes";
}

long long generateInput() {
    return 1234567890123456789LL;
}