#pragma once
#include <vector>
#include <cmath>

// struct Element {
//     size_t index;
//     double value;
// };

/* Compute z = alpha*x+y where x and y are sparse vectors. Store the result in z.
   Example:
   
   input: x=[{5, 12}, {8, 3}, {12, -1}], y=[{3, 1}, {5, -2}, {7, 1}, {8, -3}], alpha=1
   output: z=[{3, 1}, {5, 10}, {7, 1}, {12, -1}]
*/
void NO_INLINE correctSparseAxpy(double alpha, std::vector<Element> const& x, std::vector<Element> const& y, std::vector<Element>& R) {
    std::map<int, double> m;
    for(int i=0; i<x.size();i++)	
	if(m.find(x[i].index)==m.end())	m[x[i].index]  = x[i].value;
	else				m[x[i].index] += x[i].value;

    for(int i=0; i<y.size();i++)	
	if(m.find(y[i].index)==m.end())	m[y[i].index]  = y[i].value;
	else				m[y[i].index] += y[i].value;

    for(auto i = m.begin(); i != m.end(); i++)  
   	if(std::abs(i->second) > 1e-4)	R.push_back({(unsigned long)i->first, i->second});
}