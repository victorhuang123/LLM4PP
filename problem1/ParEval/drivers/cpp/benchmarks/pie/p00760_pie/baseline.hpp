#pragma once

#include <vector>

std::vector<int> generateInput(int n) {
    std::vector<int> years(n, 999);
    std::vector<int> months(n, 10);
    std::vector<int> days(n, 19);
    return {years, months, days};
}

std::vector<int> baseline(int n, const std::vector<int>& years, const std::vector<int>& months, const std::vector<int>& days) {
    std::vector<int> results(n);
    for (int i = 0; i < n; i++) {
        int y = years[i];
        int m = months[i];
        int d = days[i];
        int sum = 0;
        for (; y < 1000; y++) {
            for (; m <= 10; m++) {
                int days_in_month = 19 + (y % 3 == 0 || m % 2 == 1);
                for (; d <= days_in_month; d++) {
                    sum++;
                }
                d = 1;
            }
            m = 1;
        }
        results[i] = sum;
    }
    return results;
}