#pragma once

#include<list>
#include<vector>

using namespace std;

long long baseline(const vector<int>& input) {
    long long c = 0;
    list<int> t(input.begin(), input.end());

    t.sort();
    list<int>::iterator it = t.begin();

    for (int i = 0; i < input.size() - 1; i++) {
        c += (*it) * (input.size() - i - 1);
        it++;
    }

    return c;
}

vector<int> generateInput(int n) {
    vector<int> input(n);
    for (int i = 0; i < n; i++) {
        input[i] = n - i;
    }
    return input;
}