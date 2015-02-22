#include <iostream>
#include <set>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/assignment.hpp>
#include <boost/foreach.hpp>

namespace matrixManipulation
{
      using namespace std;
      using namespace boost::numeric::ublas;

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

      template <typename dataType>
      void rightRot(matrix<dataType> &mat,int iOrigin,int jOrigin,int matSize)
      {
            if (matSize<2) {return;}
            pair<int,int> runner(iOrigin,jOrigin),backRunner(0,0);
                        
            for (int i=0;i<matSize-1;i++)
            {
                  runner = make_pair(iOrigin,jOrigin+i);
                  for (int q=0;q<3;q++)
                  {     
                        // first transform from runner to its indices in the
                        // "relative frame" by substracting (iOrigin,jOrigin), then 
                        // find backRunner, then transform back by adding (iOrigin,jOrigin)
                        backRunner = make_pair(
                              matSize-(runner.second-jOrigin)-1+iOrigin,
                              (runner.first-iOrigin)+jOrigin); 
                        swapElement(mat,runner,backRunner);
                        runner = backRunner;
                  }
            }
            rightRot(mat,iOrigin+1,jOrigin+1,matSize-2);     
      };
      
      template <typename dataType>
      void swapElement(matrix<dataType> &mat, pair<int,int> &index1, pair<int,int> &index2)
      {
            dataType temp;
            int i = index1.first;
            int j = index1.second;
            int k = index2.first;
            int l = index2.second;
            temp = mat(i,j);
            mat(i,j) = mat(k,l);
            mat(k,l) = temp;
      };
      
      
      // 1.7
      // for elements with "target" value. set its connecting rows and columns 
      // to tne "target" value. 
      template <typename dataType>
      void tunnel(matrix<dataType> &mat, dataType target)
      {
            set<int> rowSet,colSet;
      
            for (int row=0;row<mat.size1();row++)
            {
                  for (int col=0;col<mat.size2();col++)
                  {
                        if (mat(row,col)==target)
                        { rowSet.insert(row); colSet.insert(col); }
                  }
            }
            
            BOOST_FOREACH(int row,rowSet) { setRow(mat,row,target); }
            BOOST_FOREACH(int col,colSet) { setCol(mat,col,target); }
      }
      
      template <typename dataType>
      void setRow(matrix<dataType> &mat, int row, dataType value)
      { for (int i=0;i<mat.size2();i++) { mat(row,i) = value; } };
      
      template <typename dataType>
      void setCol(matrix<dataType> &mat, int col, dataType value)
      { for (int i=0;i<mat.size1();i++) { mat(i,col) = value; } };
      
}

int main()
{
      using namespace matrixManipulation;
      using namespace boost::numeric::ublas;
 
      cout << "testing matrix rotation:" << endl;
      matrix<char> matChar(8,8);
      matChar <<= '0','0','0','0','0','0','0','0',
                  '0','0','0','0','0','0','0','0',
                  '0','0','0','0','*','0','0','0',
                  '0','0','0','0','|','0','0','0',
                  '0','0','0','0','|','0','0','0',
                  '0','0','0','0','|','0','0','0',
                  '0','0','0','0','|','0','0','0',
                  '0','0','0','0','|','0','0','0',
      printMatrix(matChar);
      rightRot(matChar,0,0,8);
      cout << "rotated is" << endl;
      printMatrix(matChar);
      
      cout << "testing setting values across row and column (tunnel):" << endl;
      matrix<int> mat(5,5);
      mat  <<=    11,12,13,14,15,
                  16,17,18,19,20,
                  21,22,23,24,25,
                  26,27,28,29,30,
                  31,32,33,34,35;
      printMatrix(mat);
      tunnel<int>(mat,23);
      cout << "tunneled for 23 is" << endl;
      printMatrix(mat);
      
      return 0;
}