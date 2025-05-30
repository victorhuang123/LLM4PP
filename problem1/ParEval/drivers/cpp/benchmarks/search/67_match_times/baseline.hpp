#pragma once
#include <vector>
#include <algorithm>

/* Return the total number of match times for `val` in vectors x and y.
   Examples:

   input: x=[1,8,4,3,2], y=[3,4,4,1,1,7], val=7
   output: 1

   input: x=[1,8,4,3,2], y=[3,4,4,1,1,7], val=1
   output: 3
*/
int NO_INLINE correctMatchTimes(std::vector<int> const& x, std::vector<int> const& y, int val) {
   int xMatch = std::count(x.begin(), x.end(), val);
   int yMatch = std::count(y.begin(), y.end(), val);

   return xMatch+yMatch;
}
