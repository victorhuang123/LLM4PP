#pragma once

#include <set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int baseline(int N, int M, string S, vector<string> queries) {
    int L = 0;
    int R = 0;
    int C = 0;

    vector<vector<int>> F(N + 1, vector<int>());

    for (int i = 0; i < M; i++) {
        string Q = queries[i];

        if (Q[0] == 'L' && Q[1] == '+') { L++; }
        if (Q[0] == 'L' && Q[1] == '-') { L--; }
        if (Q[0] == 'R' && Q[1] == '+') { R++; }
        if (Q[0] == 'R' && Q[1] == '-') { R--; }

        F[R - L + 1].push_back(L);

        C = max(C, R - L + 1);
    }

    vector<vector<int>> D(N + 1, vector<int>());

    for (int i = 1; i <= N; i++) {
        sort(F[i].begin(), F[i].end());

        if (F[i].size()) {
            D[i].push_back(F[i][0]);
        }

        for (int j = 1; j < F[i].size(); j++) {
            if (F[i][j - 1] != F[i][j]) {
                D[i].push_back(F[i][j]);
            }
        }
    }

    int Answer = 0;

    for (int i = 1; i <= C; i++) {
        set<string> s;

        for (int j = 0; j < D[i].size(); j++) {
            s.insert(S.substr(D[i][j], i));
        }

        Answer += s.size();
    }

    return Answer;
}

vector<string> generateInputQueries(int M) {
    vector<string> queries;
    for (int i = 0; i < M; i++) {
        if (i % 2 == 0) {
            queries.push_back("L+");
        } else {
            queries.push_back("R+");
        }
    }
    return queries;
}