#pragma once

#include<vector>
#include<utility>
#define ll long long int
#define MOD 1000000007

ll baseline(int n, const std::vector<ll>& t, const std::vector<ll>& a) {
    std::vector<std::pair<ll, ll>> tr(n); // t range
    std::vector<std::pair<ll, ll>> ar(n); // a range
    ll ans = 1LL;

    tr[0].first = tr[0].second = t[0];

    for (int i = 1; i < n; i++) {
        tr[i].second = t[i];
        if (t[i] > t[i - 1])
            tr[i].first = t[i];
        else
            tr[i].first = 1;
    }

    for (int i = 0; i < n; i++) {
        ar[i].second = a[i];
    }

    ar[n - 1].first = ar[n - 1].second = a[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] > a[i + 1])
            ar[i].first = a[i];
        else
            ar[i].first = 1;
    }

    for (int i = 0; i < n; i++) {
        if (ar[i].first <= tr[i].first && tr[i].second <= ar[i].second) // a-t-t-a
            ans = (ans * (tr[i].second - tr[i].first + 1)) % MOD;
        else if (tr[i].first <= ar[i].first && ar[i].second <= tr[i].second) // t-a-a-t
            ans = (ans * (ar[i].second - ar[i].first + 1)) % MOD;
        else if (ar[i].first <= tr[i].first && tr[i].first <= ar[i].second) // a-t-a-t
            ans = (ans * (ar[i].second - tr[i].first + 1)) % MOD;
        else if (tr[i].first <= ar[i].first && ar[i].first <= tr[i].second) // t-a-t-a
            ans = (ans * (tr[i].second - ar[i].first + 1)) % MOD;
        else {
            return 0;
        }
    }
    return ans;
}

std::vector<ll> generateInput(int n) {
    std::vector<ll> t(n), a(n);
    for (int i = 0; i < n; i++) {
        t[i] = i + 1;
        a[i] = n - i;
    }
    return {t, a};
}