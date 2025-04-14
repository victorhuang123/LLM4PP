#pragma once
bool isPowerOfTwo(int x) {
    return (x > 0) && !(x & (x - 1));
}

/* Apply the isPowerOfTwo function to every value in x and store the results in mask.
   Example:
   
   input: [8, 0, 9, 7, 15, 64, 3]
   output: [true, false, false, false, false, true, false]
*/
void NO_INLINE mapPowersOfTwo(std::vector<int> const& x, std::vector<bool> &mask) {
    for (int i = 0; i < x.size(); i++) {
        #if defined(USE_CUDA) || defined(USE_HIP)
        mask[i] = isPowerOfTwoHOST(x[i]);
        #else
        mask[i] = isPowerOfTwo(x[i]);
        #endif
    }
}