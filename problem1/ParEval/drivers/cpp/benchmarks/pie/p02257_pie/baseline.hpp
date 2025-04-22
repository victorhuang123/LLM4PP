#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(const vector<int>& numbers) {
    int ans = 0;
    int rant = *max_element(numbers.begin(), numbers.end());

    vector<bool> pri(++rant, 0);

    for (int i = 2; i * i < rant; i++) {
        if (!pri.at(i)) {
            for (int j = i; j * i < rant; j++) {
                pri[i * j] = true;
            }
        }
    }

    for (int num : numbers) {
        if (!pri.at(num)) {
            ans++;
        }
    }

    return ans;
}

vector<int> generateInput() {
    vector<int> numbers(1000000);
    for (int i = 0; i < 1000000; i++) {
        numbers[i] = i + 1;
    }
    return numbers;
}