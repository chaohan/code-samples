#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
public:
      int removeElement(vector<int>& nums, int val) 
      {
            int N = nums.size();
            if (N==0) {return 0;}
            
            int i=0,j=N-1;
            
            while (i<j)
            {
                  if (nums[i]==val && nums[j]==val)
                  {swap(nums,i,j-1);j--; continue;}
                  
                  if (nums[i]==val && nums[j]!=val)
                  {swap(nums,i,j);i++;j--; continue;}
                  
                  if (nums[i]!=val && nums[j]==val)
                  {j--; continue;}
                  
                  if (nums[i]!=val && nums[j]!=val)
                  {swap(nums,i+1,j);i++; continue;}
            }
            
            j=nums.size()-1;
            while (1)
            { if (nums[j]!=val) {break;} j--;}
            return j+1;
      };
      
      void swap(vector<int>& nums,int i, int j)
      {
            int temp;
            temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
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
      nums.push_back(2);
      //nums.push_back(1);
      //nums.push_back(2);
      //nums.push_back(3);
      //nums.push_back(2);
      //nums.push_back(1);
      //nums.push_back(2);
      s.print(nums);
      cout << s.removeElement(nums,3) << endl;  
      s.print(nums);
      
      return 0;
}