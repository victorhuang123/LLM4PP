#pragma once

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
namespace mp = boost::multiprecision;

static const long long MOD = 1000000007;
using Bint = mp::cpp_int;
using Real = mp::number<mp::cpp_dec_float<1024>>;

Bint baseline(long long N, const vector<Bint>& A) {
    Bint sum = 0;
    for (long long i = 0; i < N; i++) {
        sum += A[i];
    }

    Bint ans = 0;
    sum -= A[0];
    for (long long i = 0; i < N - 1; i++) {
        ans += A[i] * sum;
        ans %= MOD;
        sum -= A[i + 1];
    }

    return ans;
}

vector<Bint> generateInput(long long N) {
    vector<Bint> A(N);
    for (long long i = 0; i < N; i++) {
        A[i] = mp::cpp_int(i + 1);
    }
    return A;
}