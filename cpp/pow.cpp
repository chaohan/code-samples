#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    double myPow(double x, int n) 
    {
          //if (n<0) {cout << -n << endl;return myPow(1.0/x,-n);}
          if (n==0) {return 1;}
          if (n==1) {return x;}
          if (n==-1) {return 1.0/x;}
          return myPow(x*x,n/2) * myPow(x,n%2);
        /*
        int q = n, r = 1;
        double p = x;
        while (q>1)
        {
            p = p*p;
            q *= 1/2;
            r *= p(1+q%2);
        }
        
        return p*r;
        */
    }
};

int main()
{
      Solution s;
      
      cout << s.myPow(1.0,-2147483648) << endl;
      //cout << s.myPow(2,2) << endl;
      
      return 0;
}