#pragma once

#include <vector>
#include <algorithm>

using namespace std;
typedef long long LL;

LL baseline(LL x) {
    vector<LL> ruiseki;
    ruiseki.resize(1000000);
    ruiseki[0] = 0;

    LL i = 0;
    while(1){
        ruiseki[i+1] = ruiseki[i] + i+1;
        if(ruiseki[i+1] >= x){
            break;
        }
        i++;
    }
    return min(x, i+1);
}

vector<LL> generateInput() {
    vector<LL> input;
    input.push_back(1000000000000LL); // Example input to maximize problem scale
    return input;
}