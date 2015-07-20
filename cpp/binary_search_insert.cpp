#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
public:
    int searchInsert(vector<int>& nums, int target) 
    {
          int n = nums.size();
          if (n==0) {return 0;}
          return bs(nums,0,n-1,target);
    }
    
    int bs(vector<int>& nums, int i, int j, int target) 
    {
        if (j==i) 
        {
              if(target>nums[i]) {return i+1;}
              if(target<=nums[i]) {return i;}
        }
        
            int mid = (i+j)/2;
            if (target < nums[mid])
            {
                  if (mid-1<i) {return i;}
                  return bs(nums,i,mid-1,target); 
            }
            if (target > nums[mid])
            { 
                  if (mid+1>j) {return j;}
                  return bs(nums,mid+1,j,target); 
            }
            if (target == nums[mid]) {return mid;}
        
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
      nums.push_back(3);
      s.print(nums);
      cout << s.searchInsert(nums,0) <<endl;
      
      
      
      return 0;
}