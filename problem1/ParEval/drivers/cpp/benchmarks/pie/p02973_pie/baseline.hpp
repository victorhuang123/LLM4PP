#pragma once

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

ll baseline(int n, const vector<ll>& a) {
    multiset<ll> st;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            st.insert(a[i]);
        } else {
            auto itr = st.lower_bound(a[i]);
            if (itr != st.begin()) {
                itr--;
                st.erase(itr);
            }
            st.insert(a[i]);
        }
    }
    return st.size();
}

vector<ll> generateInput(int n) {
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}