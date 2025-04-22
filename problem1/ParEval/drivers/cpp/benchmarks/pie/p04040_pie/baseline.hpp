


#include <vector>
using namespace std;

long long baseline(long long h, long long w, long long a, long long b) {
    const long long mod = 1000000007;
    const int maxn = 200001;
    vector<long long> f(maxn);
    vector<long long> inv(maxn);
    
    f[0] = 1;
    for (int i = 1; i < maxn; ++i)
        f[i] = f[i-1] * i % mod;
    
    long long base = f[maxn-1];
    long long p = mod - 2;
    long long pow_ret = 1;
    while (p) {
        if (p & 1)
            pow_ret = pow_ret * base % mod;
        base = base * base % mod;
        p >>= 1;
    }
    inv[maxn-1] = pow_ret;
    
    for (int i = maxn-1; i >= 1; --i)
        inv[i-1] = inv[i] * i % mod;
    
    long long ret = 0;
    for (long long i = b + 1; i <= w; ++i) {
        long long n1 = h - a + i - 2;
        long long k1 = h - a - 1;
        if (k1 < 0 || n1 < k1) continue;
        long long term1 = f[n1] * inv[k1] % mod * inv[n1 - k1] % mod;
        
        long long n2 = a + w - i - 1;
        long long k2 = a - 1;
        if (k2 < 0 || n2 < k2) continue;
        long long term2 = f[n2] * inv[k2] % mod * inv[n2 - k2] % mod;
        
        ret = (ret + term1 * term2) % mod;
    }
    return ret;
}
