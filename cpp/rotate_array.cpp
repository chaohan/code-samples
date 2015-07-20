#include <iostream>
#include <vector>
using namespace std;

class Solution{
public:
void rotate(vector<int>& nums, int k) 
{
      int n = nums.size();
      if (k>=n) {k=k%n;}
      reverse(nums,0,n-1);
      reverse(nums,0,k-1);
      reverse(nums,k,n-1);
};
      
      void print(vector<int>& nums)
{
      for (int j=0;j<nums.size();j++)
      { cout << nums[j] << '-';}
      cout << endl;
};

void reverse(vector<int>& nums, int i, int j) 
{
      int n = nums.size();
      if (i>=j || n<=1) {return;}
      
      int r1 = (i<0) ? 0:i;
      int r2 = (j>=n) ? n:j;
            
      int temp;
      
      while (r1<r2)
      {
            temp = nums[r1];
            nums[r1] = nums[r2];
            nums[r2] = temp;
            r1++; r2--;
      }
};

};

int main()
{
      Solution s;
      vector<int> nums;
      for (int j=1;j<=3;j++)
           {nums.push_back(j);}
      s.rotate(nums,11);
      s.print(nums);
      
      //cout << result->val << endl;
      //cout << result->next << endl;
      //double x = pi();
      //printf("%.17g\n%.17g\n%.17g\n", nextafter(x, 0.0), x, nextafter(x, 1.0));
      return 0;
}