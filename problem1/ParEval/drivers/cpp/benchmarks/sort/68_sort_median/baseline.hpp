#pragma once

#include <algorithm>
#include <vector>

/* Given a vector x, please return its Median. The Median is the middle value in an ordered integer vector. If the size of the vector is even, there is no middle value, and the median is the mean of the two middle values.
   
   Example:

   input: [2, 3, 4]
   output: 3

   input: [2, 3]
   output: 2.5
*/

float NO_INLINE median(std::vector<int> &x) {
    if(x.size()==0)	return 0;

    std::sort(x.begin(), x.end());
    if(x.size()%2==0)	return (x[x.size()/2] + x[x.size()/2-1])/2.0;
    else  		return (float) (x[x.size()/2]);
}
