#pragma once

#include<vector>
#include<string>
#include<algorithm>

struct node {
    std::string nm; 
    int sc, id;
    bool operator <(const node &j) const {
        return nm < j.nm || (nm == j.nm && sc > j.sc);
    }
};

std::vector<int> baseline(int n, const std::vector<node>& re) {
    std::vector<node> sorted_re = re;
    std::sort(sorted_re.begin(), sorted_re.end());
    std::vector<int> result;
    for (const auto& elem : sorted_re) {
        result.push_back(elem.id);
    }
    return result;
}

std::vector<node> generate_input(int n) {
    std::vector<node> re(n);
    for (int i = 0; i < n; ++i) {
        re[i].nm = "name" + std::to_string(i % 100);
        re[i].sc = i % 1000;
        re[i].id = i + 1;
    }
    return re;
}