
#include<algorithm>
#include<vector>
using namespace std;

int baseline(const vector<char>& s) {
    const int mod = 1e9+7;
    auto add = [mod](int x) { return x >= mod ? x - mod : x; };
    int m = s.size();
    if (m == 0) return 0;

    bool flag = true;
    for (int i = 0; i < m - 1; ++i) {
        if (s[i] == s[i+1]) {
            flag = false;
            break;
        }
    }
    if (flag) return 1;

    vector<int> sum(m + 1, 0);
    vector<int> pos[3];
    for (int i = 1; i <= m; ++i) {
        int current = (s[i-1] == 'a') ? 1 : 2;
        sum[i] = (sum[i-1] + current) % 3;
        pos[sum[i]].push_back(i);
    }

    vector<int> nex(m);
    if (m > 0) {
        nex[m-1] = m;
        for (int i = m - 2; i >= 0; --i) {
            nex[i] = (s[i] == s[i+1]) ? i+1 : nex[i+1];
        }
    }

    vector<int> f(m + 1, 0);
    f[0] = 1;
    for (int i = 0; i < m; ++i) {
        f[i+1] = add(f[i+1] + f[i]);
        int c = (s[i] == 'a') ? 2 : 1;
        int target = (sum[i] + c) % 3;
        target = (target < 0) ? target + 3 : target;
        const vector<int>& v = pos[target];
        int required = nex[i] + 1;
        auto it = lower_bound(v.begin(), v.end(), required);
        if (it != v.end()) {
            int j = *it;
            if (j <= m) {
                f[j] = add(f[j] + f[i]);
            }
        }
    }

    int total_sum = sum.back();
    int ans = 0;
    for (int i = 1; i <= m; ++i) {
        if (sum[i] == total_sum) {
            ans = add(ans + f[i]);
        }
    }
    return ans;
}

