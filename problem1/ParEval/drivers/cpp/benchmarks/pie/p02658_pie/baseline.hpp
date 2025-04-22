#pragma once

#include <vector>


long long baseline(int brpkali, const std::vector<long long>& arr) {
    long long hasil = 1;
    unsigned long long Data = 1000000000000000000u;

    for (int i = 0; i < brpkali; i++) {
        if (arr[i] == 0) {
            return 0;
        }
    }

    for (int i = 0; i < brpkali; i++) {
        if (arr[i] <= (Data / hasil)) {
            hasil *= arr[i];
        } else {
            return -1;
        }
    }

    return hasil;
}