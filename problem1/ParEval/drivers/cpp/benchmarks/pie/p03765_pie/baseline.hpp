#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> generateInput() {
    vector<int> queries;
    int Q = 100000; // Maximum number of queries
    for (int i = 0; i < Q; i++) {
        queries.push_back(1); // a
        queries.push_back(100000); // b
        queries.push_back(1); // c
        queries.push_back(100000); // d
    }
    return queries;
}

vector<string> baseline(const string& S, const string& T, int Q, const vector<int>& queries) {
    vector<int> prefixS(S.size() + 1, 0);
    vector<int> prefixT(T.size() + 1, 0);

    for (int i = 1; i <= S.size(); i++) {
        prefixS[i] = prefixS[i - 1] + (S[i - 1] - '@');
        if (prefixS[i] > 2) prefixS[i] -= 3;
    }

    for (int i = 1; i <= T.size(); i++) {
        prefixT[i] = prefixT[i - 1] + (T[i - 1] - '@');
        if (prefixT[i] > 2) prefixT[i] -= 3;
    }

    vector<string> results;
    for (int i = 0; i < Q; i++) {
        int a = queries[i * 4];
        int b = queries[i * 4 + 1];
        int c = queries[i * 4 + 2];
        int d = queries[i * 4 + 3];

        int kotae = prefixS[b] - prefixS[a - 1] - prefixT[d] + prefixT[c - 1] + 6;
        while (kotae > 2) kotae -= 3;

        if (kotae == 0) {
            results.push_back("YES");
        } else {
            results.push_back("NO");
        }
    }

    return results;
}