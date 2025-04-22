#pragma once

#include <vector>

using namespace std;

typedef long long ll;

#define MOD_IS_PRIME
const ll mod = 1000000007LL;

class modlong {
public:
    modlong() { x = 0; }
    modlong(ll num) { x = adjust(num); }
    inline operator ll() const { return x; }
    inline bool operator ==(ll num) { return this->x == num; }
    inline bool operator !=(ll num) { return !(*this == num); }
    inline void operator = (ll num) { x = adjust(num); }
    inline void operator += (ll num) { x = adjust(x + num); }
    inline void operator ++() { this->operator+=(1); }
    inline modlong operator + (ll num) const { modlong m(this->x); m += num; return m; }
    inline void operator -= (ll num) { x = adjust(x - num); }
    inline void operator --() { this->operator-=(1); }
    inline modlong operator - (ll num) { modlong m(this->x); m -= num; return m; }
    inline void operator *= (ll num) { x = adjust(x * num); }
    inline modlong operator * (ll num) { modlong m(this->x); m *= num; return m; }
private:
    inline ll adjust(ll a) {
        if (a >= mod) { return a % mod; }
        if (a < 0) { return mod - 1 + ((a + 1) % mod); }
        return a;
    }
    ll x;
};

vector<ll> generate_input(int T) {
    vector<ll> N_values(T);
    for (int i = 0; i < T; i++) {
        N_values[i] = 1000000000LL + i;
    }
    return N_values;
}

modlong baseline(int T, const vector<ll>& N_values, const vector<modlong>& v_e, const vector<modlong>& v_o) {
    constexpr int K = 16;
    modlong final_result = 0;

    for (int _t = 0; _t < T; _t++) {
        ll N = N_values[_t];
        if (N % 2 == 0) { // even
            modlong ans = 0;
            modlong x = 1;
            for (int i = 0; i < K; i++) {
                ans += x * v_e[i];
                x *= N;
            }
            final_result += ans;
        } else { // odd
            modlong ans = 0;
            modlong x = 1;
            for (int i = 0; i < K; i++) {
                ans += x * v_o[i];
                x *= N;
            }
            final_result += ans;
        }
    }

    return final_result;
}