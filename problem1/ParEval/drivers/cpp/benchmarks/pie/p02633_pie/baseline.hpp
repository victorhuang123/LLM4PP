#pragma once

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef tree<int,null_type,less<int>,rb_tree_tag,
        tree_order_statistics_node_update> indexed_set;

int baseline(int N) {
    int ans = N;
    while(ans % 360 != 0){
        ans += N;
    }
    return ans / N;
}

vector<int> generateInput() {
    vector<int> input;
    for (int i = 1; i <= 1000000; ++i) {
        input.push_back(i);
    }
    return input;
}