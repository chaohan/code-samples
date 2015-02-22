#include <boost/foreach.hpp>
#include <iostream>
#include <map>
#include <string>
#include <sstream>  
//string streams is like string buffer

namespace stringAlgorithms
{
      using namespace std;
      
      // 1.5
      string charCount(string &input)
      {
            map<char,int> cache;
            char *holder;
            ostringstream result;
            
            for (int i=0;i<input.length();i++)
            {
                  holder = &input.at(i);
                  if (cache.count(*holder)>0) { cache[*holder]++; }
                  else {cache[*holder]=1;}
            }
            
            pair<char,int> iter;
            BOOST_FOREACH(iter,cache)
            { result << iter.first << iter.second; }
            
            return result.str();
      };
      
      bool isPermutation(string &s1, string &s2)
      {
            return charCount(s1)==charCount(s2);
      };
      
      // 1.8      
      bool isSubstring(string &smallString, string &largeString)
      {
            int Nsmall = smallString.length();
            int Nlarge = largeString.length();
            bool check = false;
            
            for (int i=0;i<=(Nlarge-Nsmall);i++)
            {
                  if (largeString.at(i)==smallString.at(0))
                  {     
                        check=true;
                        for (int j=1;j<Nsmall;j++)
                        {
                              check = check && (largeString.at(i+j)==smallString.at(j));
                        }
                  }
                  if (check) {break;}
            }
            return check;
      };
      
      bool isRotation(string &s1, string &s2)
      {
            string s = s1+s2;
            return isSubstring(s2,s);
      };
}
      
int main()
{
      using namespace stringAlgorithms;
      
      string str1("helloworld");
      string str2("worldhello");
      string str3("world");
      cout << "string 1 =" << charCount(str1) << endl;
      cout << "string 2 =" << charCount(str2) << endl;
      cout << "string 3 =" << charCount(str3) << endl;
      cout << "strings 1 and 2 are permutation? " << isPermutation(str1,str2) << endl;
      cout << "string 3 is a substring of string 2? " << isSubstring(str3,str2) << endl;
      cout << "string 3 is a substring of string 1? " << isSubstring(str3,str1) << endl;
      cout << "string 1 and 2 are rotations? " << isRotation(str1,str2) << endl;
      
      return 0;
}