#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    int removeDuplicates(vector<int>& nums) 
    {
          int n = nums.size();
          if (n<=2) {return n;}
        
          bool first = true;
          int i=0,j=1;
          while (j<n)
          {
                if(nums[j]==nums[i])
                {
                      if (first)
                      {
                            first = false;
                            i++;
                            nums[i] = nums[j];
                      }
                      j++;
                }
                else
                { 
                      i++;
                      if (j>=n) {break;}
                      nums[i] = nums[j];
                      j++;
                      first = true; 
                }
                //print(nums);
                //cout << "i=" << i << ", j=" << j << endl;
          }
          return i+1;
        
    }

      
void print(vector<int>& nums)
{
      for (int j=0;j<nums.size();j++)
      { cout << nums[j] << '-';}
      cout << endl;
};

};


int main()
{
      Solution s;
      vector<int> nums;
      nums.push_back(1);
      nums.push_back(1);
      //nums.push_back(2);
      //nums.push_back(2);
      /*
      nums.push_back(2);
      nums.push_back(2);
      nums.push_back(3);
      nums.push_back(3);
      nums.push_back(4);
      */
      s.print(nums);
      int loc = s.removeDuplicates(nums);
      s.print(nums);
      cout << loc << endl;
      return 0;
}