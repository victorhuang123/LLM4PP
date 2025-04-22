#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<int> generateInput(int size, int n) {
    std::vector<int> a(n);
    std::srand(std::time(0));
    for (int i = 0; i < n; i++) {
        a[i] = std::rand() % size;
    }
    return a;
}

std::string baseline(const std::vector<int>& a, int size) {
    std::vector<int> s(size, 0);
    std::stringstream result;
    for (int i = 0; i < a.size(); i++) {
        s[a[i]]++;
    }
    for (int i = 0; i < size; i++) {
        if (s[i] == 0) {
            result << "-";
        } else {
            for (int j = 0; j < s[i]; j++) {
                result << "*";
            }
        }
        result << "\n";
    }
    return result.str();
}