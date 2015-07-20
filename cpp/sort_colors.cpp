#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    
    void sortColors(vector<int>& nums) 
    {
          int n = nums.size();
          if (n<2) {return;}
          
          int N0=0,N1=0,N2=0;
          for (int j=0;j<n;j++)
          {
                if (nums[j]==0) {N0++;}
                if (nums[j]==1) {N1++;}
                if (nums[j]==2) {N2++;}
          }
          
          for (int j=0;j<N0;j++) { nums[j] = 0; }
          for (int j=N0;j<N0+N1;j++) { nums[j] = 1; }
          for (int j=N0+N1;j<N0+N1+N2;j++) { nums[j] = 2; }
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
      nums.push_back(2);
      nums.push_back(2);
      nums.push_back(0);
      nums.push_back(1);
      nums.push_back(2);
      nums.push_back(2);
      
      s.print(nums);
      s.sortColors(nums);
      s.print(nums);
      return 0;
}