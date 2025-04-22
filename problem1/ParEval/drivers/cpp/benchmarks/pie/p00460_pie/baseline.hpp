
#include <vector>

using namespace std;



int baseline(int n, int m, int s) {
    const int mod = 100000;
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(m + 1, vector<int>(s + 1, 0)));

    for(int i = 0; i < n * n; i++){
        for(int j = 1; j <= m; j++){
            for(int k = 1; k <= s; k++){
                if(i == 1){
                    if(j < k) dp[1][j][k] = 0;
                    else dp[1][j][k] = 1;
                }
                dp[(i + 1) & 1][j][k] = dp[(i + 1) & 1][j-1][k];
                if(k - j >= 0) dp[(i + 1) & 1][j][k] += dp[i & 1][j-1][k - j];
                dp[(i + 1) & 1][j][k] %= mod;
            }
        }
    }
    return dp[(n*n) & 1][m][s];
}

