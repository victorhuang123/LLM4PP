#pragma once

#include<vector>
#include<string>
#include<algorithm>

#define ll long long

ll baseline(ll a, const std::string& s) {
    ll sum = 0;
    ll max1 = 0;
    for(int i = 0; i < a; i++) {
        if(s[i] == 'I') {
            sum++;
        } else {
            sum--;
        }
        max1 = std::max(sum, max1);
    }
    return max1;
}

std::string generateInput() {
    return std::string(1000000, 'I');
}