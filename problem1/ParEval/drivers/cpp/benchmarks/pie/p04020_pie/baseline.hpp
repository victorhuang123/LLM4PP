#pragma once

#include <vector>
#include <map>
#include <queue>
#include <utility>

using namespace std;

ll baseline(ll N, vector<ll>& A) {
    ll ans = 0;
    for(int i = 1; i <= N; i++) {
        if(A[i] % 2 == 1 && A[i+1] > 0) {
            A[i]--;
            A[i+1]--;
            ans++;
        }
        ans += A[i] / 2;
    }
    return ans;
}

vector<ll> generateInput() {
    ll N = 1000000; // Large scale input to test efficiency
    vector<ll> A(N + 2, 1000000000); // Initialize with large values
    return A;
}