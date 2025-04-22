
#include <vector>

int baseline(int n) {
    std::vector<std::vector<int>> soba = {
        {200, 380},
        {300, 550},
        {500, 850}
    };

    int m = 5000 * 500;

    if (n == 0) {
        return m;
    }

    for (int i = n / soba[2][0] + 100; i >= 0; --i) {
        for (int j = n / soba[1][0] + 100; j >= 0; --j) {
            for (int k = n / soba[0][0] + 100; k >= 0; --k) {
                int w = i * soba[2][0] + j * soba[1][0] + k * soba[0][0];
                if (w == n) {
                    int p = (i / 3 * 3 * soba[2][1] * 0.88) + (i % 3 * soba[2][1]) + (j / 4 * 4 * soba[1][1] * 0.85) + (j % 4 * soba[1][1]) + (k / 5 * 5 * soba[0][1] * 0.8) + (k % 5 * soba[0][1]);
                    if (p < m) {
                        m = p;
                    }
                }
            }
        }
    }
    return m;
}

