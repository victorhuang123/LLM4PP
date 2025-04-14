#pragma once
#include <array>
#include <vector>

/* Count the number of odd and even numbers in a given integer vector x
   Examples:

   input: [7, 4, 3, 2, 1]
   output: [3, 2]

   input: [5, 3, 2 1]
   output: [3, 1]
*/
void NO_INLINE countOddEven(std::vector<int> const& x, std::array<size_t, 2> &bins) {

   bins[0] = bins[1] = 0;
   for (int i = 0; i < x.size(); i += 1) {
      if (x[i]%2==0) 	bins[1] += 1;
      else    		bins[0] += 1;
   }
}

#if defined(USE_CUDA)
// fix the issue where atomicAdd is not defined for size_t
static_assert(sizeof(size_t) == sizeof(unsigned long long), "size_t is not 64 bits");

__device__ __forceinline__ void atomicAdd(size_t* address, size_t val) {
   atomicAdd(reinterpret_cast<unsigned long long*>(address), val);
}
#endif
