

#include <vector>

using namespace std;

int baseline(int n, int p) {
    int c = 0;
    vector<int> d(n, 0);

    while (true) {
        if (p != 0) {
            d[c]++;
            p--;
        } else {
            p = d[c];
            d[c] = 0;
        }

        bool ok = (p == 0);
        if (ok) {
            for (int i = 0; i < n; i++) {
                if (i != c && d[i] != 0) {
                    ok = false;
                    break;
                }
            }
        }

        if (ok) {
            break;
        }

        c = (c + 1) % n;
    }

    return c;
}
