#pragma once
#include <vector>

struct COOElement {
   size_t row, column;
   double value;
};

/* Compute y = alpha*A*x + beta*y where alpha and beta are scalars, x and y are vectors,
   and A is a sparse matrix stored in COO format.
   x and y are length N and A is M x N.
   Example:

   input: alpha=0.5 beta=1.0 A=[{0,1,3}, {1,0,-1}] x=[-4, 2] y=[-1,1]
   output: y=[2, 3]
*/
void NO_INLINE spmv(double alpha, std::vector<COOElement> const& A, std::vector<double> const& x, double beta, std::vector<double> &y, size_t M, size_t N) {
   for (auto& element : y) {
      element *= beta;
   }
   
   for (const auto& a_ij : A) {
      if (a_ij.row < M && a_ij.column < N) {
         y[a_ij.row] += alpha * a_ij.value * x[a_ij.column];
      }
   }
}