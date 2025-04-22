
#include<vector>
#include<algorithm>
#include<cstdlib>

using namespace std;

int baseline(int N, int C, vector<int>& s, vector<int>& t, vector<int>& c) {
    vector<vector<int>> hoge(C, vector<int>(100001, 0));
    vector<vector<int>> used(C, vector<int>(100001, 0));
    vector<int> anss(100001, 0);

    for (int ch = 0; ch < C; ++ch) {
        for (int i = 0; i < N; ++i) {
            if (c[i] == ch) {
                hoge[ch][s[i]-1]++;
                hoge[ch][t[i]]--;
            }
        }
    }

    for (int ch = 0; ch < C; ++ch) {
        for (int time = 0; time < 100001; ++time) {
            if (time == 0) used[ch][time] = hoge[ch][time];
            else used[ch][time] = used[ch][time-1] + hoge[ch][time];
        }
    }

    for (int ch = 0; ch < C; ++ch) {
        for (int time = 0; time < 100001; ++time) {
            if (used[ch][time] > 0) used[ch][time] = 1;
        }
    }

    for (int time = 0; time < 100001; ++time) {
        for (int ch = 0; ch < C; ++ch) {
            anss[time] += used[ch][time];
        }
    }

    int ans = 0;
    for (int time = 0; time < 100001; ++time) {
        ans = max(ans, anss[time]);
    }

    return ans;
}

