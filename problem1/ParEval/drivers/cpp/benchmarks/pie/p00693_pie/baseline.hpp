#pragma once

#include <vector>
#include <string>
#include <utility>
#include <tuple>

using namespace std;

typedef pair<string, string> PSS;

bool eql(string s1, string s2) {
    for (int i = 0; i < s1.size(); ++i) {
        if (s1[i] != s2[i] && s2[i] != '?' && s1[i] != '?') {
            return false;
        }
    }
    return true;
}

struct Ans {
    string s1, s2, s3;
    Ans(string s1, string s2, string s3) : s1(s1), s2(s2), s3(s3) {}
};

vector<Ans> baseline(int n, int m, vector<pair<bool, PSS>> rules, vector<tuple<string, string, string>> queries) {
    vector<Ans> ans;
    for (int i = 0; i < m; ++i) {
        string s1 = get<0>(queries[i]);
        string s2 = get<1>(queries[i]);
        string s3 = get<2>(queries[i]);
        bool legal = false;
        for (int j = 0; j < n; ++j) {
            if (eql(s1, rules[j].second.first) && eql(s2, rules[j].second.second)) {
                legal = rules[j].first;
            }
        }
        if (legal) {
            ans.push_back(Ans(s1, s2, s3));
        }
    }
    return ans;
}

vector<pair<bool, PSS>> generateRules(int n) {
    vector<pair<bool, PSS>> rules;
    for (int i = 0; i < n; ++i) {
        rules.push_back(make_pair(i % 2 == 0, make_pair("rule" + to_string(i), "address" + to_string(i))));
    }
    return rules;
}

vector<tuple<string, string, string>> generateQueries(int m) {
    vector<tuple<string, string, string>> queries;
    for (int i = 0; i < m; ++i) {
        queries.push_back(make_tuple("query" + to_string(i), "address" + to_string(i), "data" + to_string(i)));
    }
    return queries;
}