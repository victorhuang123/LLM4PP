#pragma once
#include <vector>
#include <limits>

/* Return the first longest increasing contiguous subarray in the vector x.
   i.e. if x=[−2, 1, 2, 0, −1, 2, 3, −5, 4] then [-2, 1, 2], [-1, 2, 3] are both longest increasing contiguous
   subarray, but [-2, 1, 2] is the first one, thus we return [-2, 1, 2] as the result.
   Example:

   input: [−2, 1, 2, 0, −1, 2, 3, −5, 4]
   output: [-2, 1, 2]
*/
void NO_INLINE correctLongestIncreasingSubarray(std::vector<int> const& x, std::vector<int> &output) {
    //return a null array when x is null
    if(x.size()==0)	return ;

    //initialize the variables
    int longestStep = 1;
    int start=0, end=0;

    //Get the longestStep, and record its start index and end index
    for (int i = 0; i < x.size(); i++) {
        for (int j = i+1; j < x.size(); j++) {
	    if(x[i] < x[j])	{
		int step = j-i+1;
		if(step > longestStep)	{
			start = i;
			end   = j;
			longestStep = step;
		}
	    }
	    else break;
        }
    }
    
    //gather the subarray when longestStep > 1
    for(int i=start; i <= end; i++)	{
        output.push_back(x[i]);
    }
}
