#pragma once

#include<vector>
#include<algorithm>

int baseline(int n, const std::vector<char>& c) {
    int ce = 0, cw = 0, an = 1e9;
    std::vector<int> a(n);
    
    for(int i = 0; i < n; i++) {
        a[i] = cw;
        if(c[i] == 'W') cw++;
    }
    
    for(int i = n - 1; i >= 0; i--) {
        an = std::min(an, a[i] + ce);
        if(c[i] == 'E') ce++;
    }
    
    return an;
}

std::vector<char> generateInput(int n) {
    std::vector<char> c(n);
    for(int i = 0; i < n; i++) {
        c[i] = (i % 2 == 0) ? 'E' : 'W';
    }
    return c;
}