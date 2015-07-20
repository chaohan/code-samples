#include <iostream>
using namespace std;

    int mySqrt(int x) 
    {
        if (x<2) {return x;}
        int j = x,k;
        while (true)
        {
            k = (j+x/j)/2;
            if (j<=k) {return j;}
            else {j=k;}
        }
        return j;
    }
                        

int main()
{     
      
      cout << s.mySqrt(0) << endl;
      cout << s.mySqrt(1) << endl;
      cout << s.mySqrt(3) << endl;
      cout << s.mySqrt(8) << endl;
      cout << s.mySqrt(400) << endl;
      
      return 0;
}