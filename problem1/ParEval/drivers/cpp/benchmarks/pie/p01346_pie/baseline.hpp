#pragma once

#include <vector>
#include <algorithm>

using namespace std;

vector<long long> generateInput() {
    long long n = 10000;
    long long l = 1, m = 10000, r = 1;
    vector<long long> pack(n, 1);
    return {n, l, m, r, pack};
}

bool baseline(long long n, long long l, long long m, long long r, vector<long long>& pack) {
    const long long N = 10000;
    vector<vector<long long>> f(N, vector<long long>(m + 10, 0));
    
    l *= 2; m *= 2; r *= 2;
    
    f[0][0] = 1;
    f[0][1] = -1;
    
    for (long long i = 0; i <= n; ++i) {
        for (long long j = 1; j <= m; ++j)
            f[i][j] += f[i][j - 1];
        
        if (i == n) break;
        
        for (long long j = 0; j <= m; ++j) {
            if (!f[i][j]) continue;
            
            long long kl = r * pack[i], kr = l / 2 * pack[i];
            long long cl, cr;
            
            //part1
            if(j - kl >= 0 && j - kr >= 0) {
                cl = j - kr;
                cr = j - kl;
            } else if (j - kl <= 0 && j - kr <= 0) {
                cl = abs(j - kl);
                cr = abs(j - kr);
            } else {
                cl = 0;
                cr = max(abs(j - kr), abs(j - kl));
            }
            
            if(cl <= m) {
                cr = min(cr, m);
                f[i + 1][cl]++;
                f[i + 1][cr + 1]--;
            }
            
            //part2
            cl = j + kl, cr = j + kr;
            if(cl <= m) {
                cr = min(cr, m);
                f[i + 1][cl]++;
                f[i + 1][cr + 1]--;
            }
        }
    }
    
    for (long long i = 0; i <= m; ++i) {
        if (f[n][i]) {
            return true;
        }
    }
    
    return false;
}