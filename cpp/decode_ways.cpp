#include <iostream>
#include <set>
using namespace std;


int numDecodings(string s,int j) 
{
      if (j>=s.size()-1) {return 1;}
      bool notZero = (s.at(j)!='0');
      bool le26 = ( (s.at(j)-'0')<=2 && (s.at(j+1)-'0')<=6);
      return notZero*numDecodings(s,j+1) + le26 * numDecodings(s,j+2);
};

int numDecodings(string s) 
{
      if (s.size()==0 || s.at(0)=='0') {return 0;}
      return numDecodings(s,0);
      
      //if (s.size()!=0 && s.at(0)=='0') {return numDecodings(s,1);}
      //else {return numDecodings(s,0);}
      
      /*
      if (s.size()==0) {return 0;}
      if (s.at(0)=='0')  { return 0;}
      if (s.size()==2 && s.at(1)=='0') {return 1;}
      
      int count;
      if (s.at(s.size()-1)=='0') {count = -1;}
      else {count =1;}

      for (int j=s.size()-2;j>=0;j--)
      {
            if ( ((s.at(j)-'0')<=2 && (s.at(j+1)-'0')<=6) && s.at(j)!='0')
            {count++;}
            if (s.at(j)=='0') {count--;}
            if (s.at(j)=='0' && s.at(j+1)=='0')
            {return 0;}
      }

      return count;
      */
}



int main()
{
      string s;
      
      s = "100";
      cout << s << ": "<< numDecodings(s) << endl;
      s = "110";
      cout << s << ": "<< numDecodings(s) << endl;
      s = "1001";
      cout << s << ": "<< numDecodings(s) << endl;
      s = "1010";
      cout << s << ": "<< numDecodings(s) << endl;
      s = "101";
      cout << s << ": "<< numDecodings(s) << endl;
      s = "123";
      cout << s << ": "<< numDecodings(s) << endl;
      
      
      //cout << result->val << endl;
      //cout << result->next << endl;
      //double x = pi();
      //printf("%.17g\n%.17g\n%.17g\n", nextafter(x, 0.0), x, nextafter(x, 1.0));
      return 0;
}