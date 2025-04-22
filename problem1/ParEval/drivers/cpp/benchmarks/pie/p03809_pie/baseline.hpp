#pragma once

#include <vector>
#include <utility>

using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> PII;

const int MAX = 200*1000+47;

VI G[MAX];
int A[MAX];

bool ok;

LL DFS(int v, int p)
{
    LL val = A[v];
    bool leaf = (G[v].size() == 1);
    if (!leaf) val *= 2;
    LL ans = val;
    for (int i = 0; i < G[v].size(); ++i)
    {
        int to = G[v][i];
        if (to == p) continue;
        LL res = DFS(to, v);
        if (!leaf && res * 2 > val) ok = false;
        ans -= res;
    }
    
    if (!leaf && ans * 2 > val) ok = false;
    if (ans < 0) ok = false;
    return ans;
}

bool baseline(int n, VI& A, vector<PII>& edges)
{
    for (int i = 0; i < n-1; ++i)
    {
        int a = edges[i].first, b = edges[i].second;
        --a, --b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    ok = true;
    return (DFS(0, -1) == 0 && ok);
}

vector<PII> generateExampleInput(int n)
{
    vector<PII> edges;
    for (int i = 1; i < n; ++i)
    {
        edges.push_back({i, i+1});
    }
    return edges;
}