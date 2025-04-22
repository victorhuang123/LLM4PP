
#include <vector>
#include <string>

long long baseline(const std::string& s) {
    long long n = s.size();
    long long ans = 0;
    long long c = 0;

    for (long long i = 0; i < n; i++) {
        if (s[i] == 'S') {
            c++;
        } else {
            if (c > 0) ans++;
            c = (c > 0) ? c - 1 : 0;
        }
    }
    return n - 2 * ans;
}

