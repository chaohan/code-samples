#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
public:
    vector<int> searchRange(vector<int>& nums, int target)
    {
          int n = nums.size();
          
          vector<int> result;
          result.push_back(-1);result.push_back(-1);
          if (n==0) {return result;}
          
          result[0] = searchHead(nums,0,n-1,target);
          result[1] = searchTail(nums,0,n-1,target);
      
          return result;
    }
    
    int searchHead(vector<int>& nums, int i, int j, int target) 
    {
          if (j<i) {return -1;}
          if (i==j) {return nums[i]==target ? i:-1;}
          
          int mid = (i+j)/2;
          
          if (target>nums[mid]) 
          { return searchHead(nums,mid+1,j,target); }
          
          if (target<nums[mid]) 
          { return searchHead(nums,i,mid-1,target); }
          
          if (mid>0 && target==nums[mid-1]) 
          {return searchHead(nums,i,mid-1,target); }
          
          return mid;
    } 
      
    int searchTail(vector<int>& nums, int i, int j, int target) 
    {
          if (j<i) {return -1;}
          if (i==j) {return nums[i]==target ? i:-1;}
          
          int mid = (i+j)/2;
          
          if (target<nums[mid]) 
          { return searchTail(nums,i,mid-1,target); }
          
          if (target>nums[mid] || target==nums[mid+1]) 
          { return searchTail(nums,mid+1,j,target); }
          
          return mid;
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
      vector<int> nums,result;
      nums.push_back(2);
      nums.push_back(2);
                
      s.print(nums);
      
      //result = s.searchRange(nums,0);
      //cout << result[0] << ',' << result[1] << endl;
      cout << s.searchHead(nums,0,nums.size()-1,1) << endl;
      //cout << s.searchTail(nums,0,nums.size()-1,3) << endl;
      
      return 0;
}