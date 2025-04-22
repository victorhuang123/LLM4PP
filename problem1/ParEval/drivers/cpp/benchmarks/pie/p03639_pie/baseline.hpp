#pragma once

#include <vector>
#include <string>

using namespace std;

string baseline(int n, const vector<int>& numbers) {
    int a = 0, b = 0, c = 0;
    for(int x : numbers) {
        if(x % 4 == 0) {
            a++;
        } else if(x % 2 == 0) {
            b++;
        } else {
            c++;
        }
    }

    if(a > c - 1) {
        return "Yes";
    } else {
        if(a == c - 1 && b == 0) {
            return "Yes";
        }
        return "No";
    }
}

vector<int> generateInput(int n) {
    vector<int> numbers(n);
    for(int i = 1; i <= n; ++i) {
        numbers[i - 1] = i;
    }
    return numbers;
}