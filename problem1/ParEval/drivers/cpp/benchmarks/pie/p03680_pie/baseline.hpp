#pragma once

#include<vector>

struct A {
    int is = 0;
    int num;
};

int baseline(const std::vector<A>& pp) {
    std::vector<A> pp_copy = pp;
    pp_copy[1].is = 1;
    int y = 0;
    int Count = 0, t = 1;

    while (pp_copy[2].is != 1) {
        pp_copy[t].is = 1;
        t = pp_copy[t].num;
        Count++;

        if (Count > 200000) {
            y = 1;
            break;
        }
    }

    if (!y) {
        return Count - 1;
    } else {
        return -1;
    }
}

std::vector<A> generateInput() {
    std::vector<A> pp(200001);
    for (int i = 0; i < 200000; ++i) {
        pp[i].num = i + 1;
    }
    pp[200000].num = 2;
    return pp;
}