#pragma once

#include <string>
#include <algorithm>
#include <cmath>

std::string baseline(long long sx, long long sy, long long tx, long long ty) {
    long long stx = tx - sx;
    long long sty = ty - sy;
    std::string result;

    for(int i = 0; i < sty; i++) {
        result += 'U';
    }
    for(int i = 0; i < stx; i++) {
        result += 'R';
    }
    for(int i = 0; i < sty; i++) {
        result += 'D';
    }
    for(int i = 0; i < stx; i++) {
        result += 'L';
    }
    result += 'L';
    for(int i = 0; i <= sty; i++) {
        result += 'U';
    }
    for(int i = 0; i <= stx; i++) {
        result += 'R';
    }
    result += 'D';
    result += 'R';
    for(int i = 0; i <= sty; i++) {
        result += 'D';
    }
    for(int i = 0; i <= stx; i++) {
        result += 'L';
    }
    result += 'U';

    return result;
}