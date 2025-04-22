


#include <vector>
#include <queue>
#include <climits>

using namespace std;

int baseline(int k) {
    if (k <= 1) return 1;

    vector<vector<pair<int, int>>> adj(k);
    for (int j = 0; j < k; ++j) {
        adj[j].emplace_back((j + 1) % k, 1);
        adj[j].emplace_back((j * 10) % k, 0);
    }

    vector<int> d(k, INT_MAX);
    vector<bool> in_queue(k, false);
    queue<int> q;

    d[1] = 0;
    q.push(1);
    in_queue[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }

    return d[0] + 1;
}

