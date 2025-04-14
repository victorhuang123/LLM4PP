#pragma once

#include <algorithm>
#include <vector>

/* Sort the vector x in ascending order ignoring elements with value 0.
   Leave zero valued elements in-place.
   Example:
   
   input: [8, 4, 0, 9, 8, 0, 1, -1, 7]
   output: [-1, 1, 0, 4, 7, 0, 8, 8, 9]
*/
void NO_INLINE sortIgnoreZero(std::vector<int> &x) {
    std::vector<int> nonZeroElements;
    for (int num : x) {
        if (num != 0) {
            nonZeroElements.push_back(num);
        }
    }

    std::sort(nonZeroElements.begin(), nonZeroElements.end());

    size_t nonZeroIndex = 0;
    for (int i = 0; i < x.size(); i += 1) {
        if (x[i] != 0) {
            x[i] = nonZeroElements[nonZeroIndex];
            nonZeroIndex += 1;
        }
    }
}
