#include <iostream>
#include <vector>
using namespace std;

/*
bool searchMatrix(vector<vector<int>> &matrix,int target) 
{      
        retrun false;
};
*/

bool binarySearchVector(vector<int> &vector, int a, int b, int target)
{
      if (a==b) {return target==vector[a];}
      
      int mid = vector[(a+b)/2];
      if (target < mid) {return binarySearchVector(vector,a,(a+b)/2,target); }
      if (target > mid) {return binarySearchVector(vector,(a+b)/2+1,b,target); }
      return true;
};

int main()
{
      vector<int> v;
      v.push_back(0);
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);
            
      for (int j=0;j<v.size();j++)
      { cout << v[j] << endl;}
      
      
      //cout << result->val << endl;
      //cout << result->next << endl;
      //double x = pi();
      //printf("%.17g\n%.17g\n%.17g\n", nextafter(x, 0.0), x, nextafter(x, 1.0));
      return 0;
}