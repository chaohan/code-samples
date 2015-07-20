#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
public:
    int findPeakElement(vector<int>& nums) 
    {
          int n = nums.size();
          if (n==1) {return 0;}
          return fpe(nums,0,n-1);
    };
    
    int fpe(vector<int>& nums, int i, int j) 
    {
          if (j==i) {return j;}
          int mid = (i+j)/2;
          
          if (mid==0) 
          {
                return (nums[mid]>nums[mid+1])? mid:mid+1;
          }
          
          if (nums[mid+1]>nums[mid]) 
          { return fpe(nums,mid+1,j); }
          
          if (nums[mid-1]>nums[mid]) 
          { return fpe(nums,i,mid-1); }
          
          return mid;
    }; 
      
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
      vector<int> nums,result;
      nums.push_back(100);
      nums.push_back(1000);
      //nums.push_back(3);
      //nums.push_back(10);
      //nums.push_back(10000);
                
      s.print(nums);
      
      cout << s.findPeakElement(nums) << endl;
      
      
      return 0;
}