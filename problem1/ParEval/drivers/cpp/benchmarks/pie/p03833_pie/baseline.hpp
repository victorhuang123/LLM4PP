#pragma once

#include <vector>
#include <algorithm>
#include <emmintrin.h>

using namespace std;

typedef long long ll;

static inline __m128i __attribute__((always_inline))
po_mm_max_epi32(__m128i a, __m128i b){
  __asm__("pmaxsd %1, %0" : "+x" (a) : "xm" (b));
  return a;
}

ll baseline(const vector<unsigned int>& a, const vector<vector<unsigned int>>& b) {
    int n = a.size();
    int m = b[0].size();
    vector<unsigned int> mx(m, 0);
    unsigned long long tmp[2] __attribute__((aligned(16)));
    ll ans = 0;

    for (int l = 0; l < n; ++l) {
        ll lensum = 0;
        fill(mx.begin(), mx.end(), 0);

        for (int i = 0; i < m; i += 4) {
            __m128i xx = _mm_load_si128((__m128i*)(mx.data() + i));
            __m128i yy = _mm_load_si128((__m128i*)(b[l].data() + i));
            xx = po_mm_max_epi32(xx, yy);
            _mm_store_si128((__m128i*)(mx.data() + i), xx);
        }

        __m128i x = _mm_setzero_si128();
        __m128i y = _mm_setzero_si128();
        const __m128i zero = _mm_setzero_si128();

        for (int i = 0; i < m; i += 4) {
            __m128i xx = _mm_load_si128((__m128i*)(mx.data() + i));
            __m128i yy = _mm_unpackhi_epi32(xx, zero);
            xx = _mm_unpacklo_epi32(xx, zero);
            x = _mm_add_epi64(x, xx);
            y = _mm_add_epi64(y, yy);
        }
        x = _mm_add_epi64(x, y);
        _mm_store_si128((__m128i*)tmp, x);
        ll current = tmp[0] + tmp[1];
        ans = max(ans, current - lensum);

        for (int r = l + 1; r < n; ++r) {
            lensum += a[r - 1];

            for (int i = 0; i < m; i += 4) {
                __m128i xx = _mm_load_si128((__m128i*)(mx.data() + i));
                __m128i yy = _mm_load_si128((__m128i*)(b[r].data() + i));
                xx = po_mm_max_epi32(xx, yy);
                _mm_store_si128((__m128i*)(mx.data() + i), xx);
            }

            x = _mm_setzero_si128();
            y = _mm_setzero_si128();

            for (int i = 0; i < m; i += 4) {
                __m128i xx = _mm_load_si128((__m128i*)(mx.data() + i));
                __m128i yy = _mm_unpackhi_epi32(xx, zero);
                xx = _mm_unpacklo_epi32(xx, zero);
                x = _mm_add_epi64(x, xx);
                y = _mm_add_epi64(y, yy);
            }
            x = _mm_add_epi64(x, y);
            _mm_store_si128((__m128i*)tmp, x);
            current = tmp[0] + tmp[1];
            ans = max(ans, current - lensum);
        }
    }
    return ans;
}

vector<unsigned int> generate_a(int n) {
    vector<unsigned int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % 1000000;
    }
    return a;
}

vector<vector<unsigned int>> generate_b(int n, int m) {
    vector<vector<unsigned int>> b(n, vector<unsigned int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            b[i][j] = rand() % 1000000;
        }
    }
    return b;
}