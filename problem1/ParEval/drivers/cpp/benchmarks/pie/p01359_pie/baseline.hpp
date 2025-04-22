#pragma once

#include <vector>
#include <string>

using namespace std;

vector<string> baseline(int n, int m, const vector<vector<string>>& name, const vector<pair<long long, long long>>& data, const vector<long long>& queries) {
    vector<string> results;
    vector<long long> japan(n + 1);
    vector<long long> japan2(n + 1);

    for (int i = 1; i <= n; i++) {
        japan[i] = data[i - 1].second;
        japan2[i] = data[i - 1].second - data[i - 1].first;
    }

    for (long long query : queries) {
        bool found = false;
        for (int j = 1; j <= n; j++) {
            if (query <= japan[j] && query > japan2[j]) {
                results.push_back(name[j - 1][0] + " " + to_string(query - japan2[j]));
                found = true;
                break;
            }
        }
        if (!found) {
            results.push_back("Unknown");
        }
    }

    return results;
}

vector<vector<string>> generateInputNames(int n) {
    vector<vector<string>> names(n, vector<string>(1, "Name"));
    return names;
}

vector<pair<long long, long long>> generateInputData(int n) {
    vector<pair<long long, long long>> data(n, {1, 1000000});
    return data;
}

vector<long long> generateInputQueries(int m) {
    vector<long long> queries(m, 500000);
    return queries;
}