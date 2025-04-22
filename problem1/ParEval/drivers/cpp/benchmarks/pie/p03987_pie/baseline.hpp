#pragma once

#include <vector>
#include <stack>
#include <cstring>

long long baseline(long long n, const std::vector<long long>& a) {
    std::vector<long long> s(n + 1, 0);
    std::vector<long long> stack(n + 2, 0);
    std::vector<long long> l(n + 1, 0);
    std::vector<long long> r(n + 1, 0);

    for (long long i = 1; i <= n; i++) {
        s[i] = s[i - 1] + a[i - 1];
    }

    long long top = 0;
    for (long long i = 1; i <= n; i++) {
        while (top && a[i - 1] <= a[stack[top] - 1]) {
            top--;
        }
        l[i] = stack[top] + 1;
        top++;
        stack[top] = i;
    }

    memset(stack.data(), 0, stack.size() * sizeof(long long));
    top = 0;
    for (long long i = n; i >= 1; i--) {
        while (top && a[i - 1] <= a[stack[top] - 1]) {
            top--;
        }
        r[i] = stack[top] - 1;
        top++;
        stack[top] = i;
    }

    long long ans = 0;
    for (long long i = 1; i <= n; i++) {
        long long left = l[i], right = r[i];
        if (right == -1) right = n;
        ans += (i - left + 1) * a[i - 1] * (right - i + 1);
    }

    return ans;
}

std::vector<long long> generateInput(long long n) {
    std::vector<long long> a(n);
    for (long long i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}