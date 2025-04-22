#include <vector>

using namespace std;

int baseline(int n, const vector<int>& a) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int num = a[i];
        while (num % 2 == 0) {
            cnt++;
            num /= 2;
        }
    }
    return cnt;
}

