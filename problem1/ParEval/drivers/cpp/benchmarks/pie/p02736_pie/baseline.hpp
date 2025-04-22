#pragma once

#include <vector>
#include <string>

using namespace std;

int baseline(int n, const string& s) {
    int cnt[4] = {0}, fact[] = {1, 1, 2, 6};
    vector<int> vec;
    bool ans = 0;

    for (int i = 0; i < n; ++i) {
        if ((i & (n - 1)) == i)
            ans = (ans + s[i] - 48) % 2;
    }

    for (int i = 1; i < n; ++i) {
        int q = s[i - 1] - 48, w = s[i] - 48;
        ++cnt[abs(q - w)];
        vec.push_back(abs(q - w));
    }

    if (!cnt[1]) {
        int sum = 0;
        for (int i = 0; i < n - 1; ++i) {
            int q = i, w = n - 2, p = 1;
            while (q) {
                if ((w % 4) < (q % 4))
                    p = 0;
                else
                    p *= (fact[w % 4] / fact[q % 4] / fact[(w % 4) - (q % 4)]) % 4;
                q /= 4;
                w /= 4;
            }
            sum += p * vec[i];
            sum %= 4;
        }
        return sum;
    } else {
        return ans;
    }
}

string generateInput(int n) {
    string s(n, '0');
    for (int i = 0; i < n; ++i) {
        s[i] = '0' + (i % 2);
    }
    return s;
}