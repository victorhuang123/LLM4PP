#pragma once

#include <vector>
#include <set>
#include <algorithm>
#include <sstream>

using namespace std;

int baseline(int n, int k, const set<char>& st) {
    for(int i = n; i <= 100000; ++i) {
        string str = to_string(i);
        bool valid = true;
        for(char ch : str) {
            if(st.find(ch) != st.end()) {
                valid = false;
                break;
            }
        }
        if(valid) {
            return i;
        }
    }
    return -1;
}

vector<int> generate_input() {
    vector<int> input;
    input.push_back(1); // n
    input.push_back(3); // k
    set<char> st = {'1', '2', '3'};
    input.push_back(st.size()); // size of set
    return input;
}