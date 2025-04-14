#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <limits>
#include <climits>

/* Return the length of the shortest path from any source to any dest in the undirected graph defined by the adjacency matrix A
using floyd algorithm.
   A is an NxN adjacency matrix stored in row-major. Assume the graph is connected. A is undirected.
   Example:
   
   input: [[0, 1, 1, 0], [1, 0, 0, 1], [1, 0, 0, 1], [0, 1, 1, 0]]
   output: [[0, 1, 1, 2], [1, 0, 2, 1], [1, 2, 0, 1], [2, 1, 1, 0]]
*/
void NO_INLINE floyd(std::vector<int> const& A, size_t N, std::vector<int>& R) {
    R = A;
   for(int k=0; k<N; k++) {
       for(int i=0; i<N; i++) {
           for(int j=0; j<N; j++) {
               R[i*N+j] = std::min(R[i*N+j], R[i*N+k]+R[k*N+j]);
           }
       }
   }
}
