#pragma once

int baseline(int x, int y, int z) {
    int s = 0;
    x -= z;
    while ((x - y - z) >= 0) {
        s++;
        x = x - y - z;
    }
    return s;
}