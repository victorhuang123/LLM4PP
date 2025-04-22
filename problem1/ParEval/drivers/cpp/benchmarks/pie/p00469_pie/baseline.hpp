#pragma once

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

vector<string> generateInput(int n) {
    vector<string> integer(n + 1);
    for (int i = 1; i <= n; ++i) {
        integer[i] = to_string(i);
    }
    return integer;
}

int baseline(int n, int k, const vector<string>& integer) {
    vector<string> num;
    vector<int> chousen(n + 1, 0);
    unordered_set<string> complete_integer;
    string answer;

    function<void()> operation = [&]() {
        for (int i = 1; i <= n; i++) {
            if (chousen[i] == 0) {
                chousen[i] = 1;
                num.push_back(integer[i]);

                if (num.size() == k) {
                    for (int j = 1; j <= k; j++) {
                        answer += num[j - 1];
                    }
                    if (complete_integer.find(answer) == complete_integer.end()) {
                        complete_integer.insert(answer);
                    }
                    answer = "";
                } else {
                    operation();
                }
                num.pop_back();
                chousen[i] = 0;
            }
        }
    };

    operation();
    return complete_integer.size();
}