

#include<vector>
#include<utility>
#include<algorithm>
#include<climits>

using namespace std;

long long int baseline(int n, int m, const vector<pair<int, int>>& edges, const vector<long long int>& weights) {
    vector<long long int> dis(n, LLONG_MAX);
    bool neg_cycle = false;
    
    for (int x = 0; x < n; ++x) {
        fill(dis.begin(), dis.end(), LLONG_MAX);
        dis[x] = 0;
        
        for (int i = 0; i <= n + 1; ++i) {
            for (int j = 0; j < m; ++j) {
                long long int u = edges[j].first;
                long long int v = edges[j].second;
                if (i >= (n - 1)) {
                    if ((dis[u] + weights[j] < dis[v]) && dis[u] != LLONG_MAX)
                        neg_cycle = true;
                } else {
                    if (dis[u] != LLONG_MAX) {
                        dis[v] = min((dis[u] + weights[j]), dis[v]);
                    }
                }
            }
        }
        
        if (neg_cycle) {
            return -1;
        }
    }
    
    long long int total_distance = 0;
    for (long long int d : dis) {
        if (d != LLONG_MAX) {
            total_distance += d;
        }
    }
    
    return total_distance;
}

