#pragma once

#include <vector>
#include <algorithm>

using namespace std;

struct Knife {
    int iHurt;
    int iType = 0;
};

bool cmp(Knife nifKnife1, Knife nifKnife2) {
    return (nifKnife1.iHurt > nifKnife2.iHurt);
}

int baseline(int n, int iHP, vector<Knife> arrKnives) {
    sort(arrKnives.begin(), arrKnives.end(), cmp);
    int iSum = 0;
    for (int i = 0; i < arrKnives.size(); ++i) {
        if (arrKnives[i].iType == 1) {
            ++iSum;
            iHP -= arrKnives[i].iHurt;
            if (iHP <= 0) {
                return iSum;
            }
        } else if (arrKnives[i].iType != 1) {
            if (iHP % arrKnives[i].iHurt == 0)
                iSum += iHP / arrKnives[i].iHurt;
            else
                iSum += iHP / arrKnives[i].iHurt + 1;
            return iSum;
        }
    }
    return iSum;
}

vector<Knife> generateInput(int n) {
    vector<Knife> arrKnives(n);
    for (int i = 0; i < n; ++i) {
        arrKnives[i].iHurt = rand() % 1000 + 1;
        arrKnives[i].iType = rand() % 2;
    }
    return arrKnives;
}