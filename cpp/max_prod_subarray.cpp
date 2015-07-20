#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) 
    {
       return mp(nums,0,nums.size()-1);
    };
    
    int mp(vector<int>& nums,int i, int j) 
    {
        if (i>j) {return 0;}
        if (nums[i]==0) {return mp(nums,i+1,j);}
        //if (nums[j]==0) {return mp(nums,i,j-1);}
        if (i==j) {return nums[i];}
        
        vector<int> zeros;
        zeros = find_zeros(nums,i,j);
        if (zeros.size()==0)
        {
           int k,front=1,back=1,total=1;
           for (k=i;k<=j;k++)
           {
               total *= nums[k];
           }
           if (total<0)
           {
               // calculate value with omitting front neg 
               k=i;
               front = total;
               while (nums[k]>0)
               {
                   front = front/nums[k];
                   k++;
               }
               front = front/nums[k];
               
               // calculate value with omitting back neg 
               k=j;
               back = total;
               while (nums[k]>0)
               {
                   back = back/nums[k];
                   k--;
               }
               back = back/nums[k];
               
               return max(front,back);
           }
           else
           {
               return total;
           }
        }
        else
        {
           vector<int> maxes;
           maxes.push_back(mp(nums,i,zeros[0]-1));
           for (int k=1;k<zeros.size();k++)
           {
               maxes.push_back(mp(nums,zeros[k-1]+1,zeros[k]-1));
           }
           maxes.push_back(mp(nums,zeros[zeros.size()-1]+1,j));
           //print(maxes);
           int max = maxes[0];
           for (int k=1;k<maxes.size();k++)
           {
               if (maxes[k]>max) {max = maxes[k];}
           }
           return (max<0)? 0:max;
        }
    };
    
    // check if nums contains zero, return their indices; first entry always 0
    vector<int> find_zeros(vector<int> &nums,int i, int j)
    {
        vector<int> zeros;
        for (int k=i;k<=j;k++)
        {
           if (nums[k]==0) {zeros.push_back(k);}
        }
        return zeros;
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
      
      vector<int> nums;
      //nums.push_back(-2);
      nums.push_back(0);
      nums.push_back(-2);
      nums.push_back(0);
      //nums.push_back(-2);
      
      cout << s.maxProduct(nums) << endl;
      //cout << nums[9] << endl;
      
 
      return 0;
}