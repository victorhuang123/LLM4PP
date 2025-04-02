#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>

/* Given an integer array x. You can choose a set of integers and remove all the occurrences of these integers in the array.
   Return the minimum size of the set so that at least half of the integers of the array are removed.

   Example:

   input: x=[[3, 3, 3, 3, 5, 5, 5, 2, 2, 7]
   output: 2
   explanation: Choosing {3,7} will make the new array [5,5,5,2,2] which has size 5 (i.e equal to half of the size of the old array).
Possible sets of size 2 are {3,5},{3,2},{5,2}.
Choosing set {2,7} is not possible as it will make the new array [3,3,3,3,5,5,5] which has a size greater than half of the size of the old array.

   input: x = [7,7,7,7,7,7]
   output: 1
   explanation: The only possible set you can choose is {7}. This will make the new array empty.
*/
int NO_INLINE correctCorrectReduceArrayToHalf(std::vector<int> const& x) {
    std::unordered_map<int, int> counter;
    std::priority_queue<int> q;
    int res = 0, removed = 0;
        
    for (auto a : x) 	   counter[a]++;
    for (auto c : counter) q.push(c.second);
        
    while (removed < x.size() / 2) {
        removed += q.top();
        q.pop();
        res++;
    }
        
    return res;
}
