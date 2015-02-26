#include <iostream>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/assignment.hpp>
#include <boost/math/special_functions/binomial.hpp>

namespace recursionAlgorithms
{      
      using namespace std;
      using namespace boost::numeric::ublas;
            
      /*9.1
            count ways to cover N steps by hopping either 
            1,2 or 3 steps at a time
      */
      int waysToHopSlow(int N)
      {
            if (N==1 || N==0) { return 1; }
            if (N<0) { return 0; }
            return waysToHopSlow(N-1)+waysToHopSlow(N-2)+waysToHopSlow(N-3);
      };
      
      int waysToHopFast(int N, std::vector<int> &cache)
      {
            if (N==0 || N==1) { return 1; }
            if (N<0) { return 0; }
            if (cache[N]>0) { return cache[N]; }
            cache[N] = waysToHopFast(N-1,cache)
                        + waysToHopFast(N-2,cache)
                        + waysToHopFast(N-3,cache);
            return cache[N];
      };
      
      /*9.2
            Return the number of ways connecting the top-left corner
            of a MxN matrix/grid to the bottom-right corner,
            going only downward and rightward.
            Off-limits grid points are allow by specifying a -1 value
            in the cache input matrix
      */
      int ways2D(int r, int c, matrix<int> &cache)
      {
            if (r == cache.size1()-1 && c == cache.size2()-1 ) { return 1;}
            if (r >= cache.size1() || c >= cache.size2() || cache(r,c) == -1) 
            { return 0; }
            if (cache(r,c)>0) { return cache(r,c); }
            
            cache(r,c) = ways2D(r,c+1,cache) + ways2D(r+1,c,cache);
            return cache(r,c);
      };
      
      template <typename dataType>
      void printMatrix(matrix<dataType> &mat)
      {
            for (int row=0;row<mat.size1();row++)
            {
                  for (int col=0;col<mat.size2()-1;col++)
                  { cout << mat(row,col) << " "; }
                  cout << mat(row,mat.size2()-1) << endl;
            }
      };
};


int main()
{
      using namespace recursionAlgorithms;
      using namespace boost::math;
            
      //matrix<int> input(12,1);
      //input <<= 1,0,1,2,2,1,3,3,3,0,10,11;
      
      // test 9.1
      //int Nin = 35;
      //std::vector<int> cache(Nin,0);
      //cout << waysToHopSlow(Nin) << endl;   
      //cout << waysToHopFast(Nin,cache) << endl;   
      
      // test 9.2
      int M,N;
      M = 10; N= 10;
      matrix<int> input(M,N);
      //input(1,1) = -1;
      printMatrix(input);
      cout << "calculated number of ways = "<< ways2D(0,0,input) << endl;
      cout << "true number of ways = "  << binomial_coefficient<double>(M+N-2,M-1) << endl;
      printMatrix(input);
      
      
      
      
      return 0;
}