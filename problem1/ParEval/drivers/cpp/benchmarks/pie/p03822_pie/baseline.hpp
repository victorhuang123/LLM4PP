
#include <vector>
#include <algorithm>
using namespace std;

int baseline(int N, const vector<int>& input) {
    vector<vector<int>> children(N + 1);
    for (int i = 2; i <= N; ++i) {
        int a = input[i - 2];
        children[a].push_back(i);
    }

    vector<int> memo(N + 1, 0);
    for (int a = N; a >= 1; --a) {
        vector<int> kari;
        for (int child : children[a]) 
            kari.push_back(memo[child]);
        sort(kari.rbegin(), kari.rend());
        int ret = 1;
        for (int i = 0; i < kari.size(); ++i)
            ret = max(ret, i + 1 + kari[i]);
        memo[a] = ret;
    }
    return memo[1] - 1;
}

