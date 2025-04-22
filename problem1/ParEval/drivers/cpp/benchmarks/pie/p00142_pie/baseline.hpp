

#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <deque>
#include <cstdio>
#include <cmath>

using namespace std;

#define reep(i,f,t) for(int i=f ; i<int(t) ; ++i)
#define rep(i,n) reep(i, 0, n)



vector<int> baseline(const vector<int>& nums) {
    int n = nums.size();
    vector<int> result;
    reep(i, 1, (n + 1) / 2) {
        int sum = 0;
        rep(j, n) {
            sum += nums[j] & nums[(j + i) % n];
        }
        result.push_back(sum * 2);
    }
    return result;
}
