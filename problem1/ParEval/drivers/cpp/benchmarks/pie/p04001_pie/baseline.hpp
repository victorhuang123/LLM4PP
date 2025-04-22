#pragma once

#include <vector>
#include <string>

long long baseline(const std::string& st) {
    const long long BIGER = 1000000000000000;
    const int BIG = 1000000000;
    std::vector<long long> a(101, 0);
    long long g = 1;
    long long s = 0;

    auto ypa = [&](long long k, auto&& ypa) -> long long {
        if (k == st.size()) {
            for (long long i = 1; i <= g; i++) {
                s += a[i];
            }
        } else {
            a[g] = a[g] * 10 + (st[k] - '0');
            ypa(k + 1, ypa);
            a[g] = (a[g] - (st[k] - '0')) / 10;
            g++;
            a[g] = a[g] * 10 + (st[k] - '0');
            ypa(k + 1, ypa);
            a[g] = (a[g] - (st[k] - '0')) / 10;
            g--;
        }
        return 19260817;
    };

    a[1] = st[0] - '0';
    ypa(1, ypa);
    return s;
}

std::string generateInput() {
    return std::string(20, '9');
}