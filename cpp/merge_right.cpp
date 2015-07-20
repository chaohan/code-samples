#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
    {
          int i=m-1,j=n-1,k=nums1.size()-1;
          while (i>=0 && j>=0)
          {
                if (nums2[j] >= nums1[i])
                {
                      nums1[k] = nums2[j];
                      j--;
                }
                else 
                {
                      nums1[k] = nums1[i];
                      i--;
                }
                k--;
          }
          i = j;
          while (j>=0)
          {
                nums1[i] = nums2[j];
                i--; j--;
          }
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
      vector<int> nums1,nums2;
      for (int j=101;j<=110;j++)
           {nums1.push_back(j);}
      for (int j=1;j<=3;j++)
           {nums2.push_back(j);}
      
      s.merge(nums1,7,nums2,3);
      s.print(nums1);
      return 0;
}