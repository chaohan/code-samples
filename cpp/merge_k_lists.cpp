#include <iostream>
#include <vector>
using namespace std;


 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    
      ListNode* mergeKLists(vector<ListNode*>& lists) 
    {
        int n = lists.size();
        if (n==0) {return NULL;}
        if (n==1) {return lists[0];}
        
        ListNode *h1,*h2;
        vector<ListNode*> front_half, back_half;
        for (int j=0;j<=n/2;j++)
        { 
              if(lists[j]) {front_half.push_back(lists[j]);}
        }
        
        for (int j=n/2+1;j<n;j++)
        { 
              if(lists[j]) {back_half.push_back(lists[j]);}
        }
            
        h1 = mergeKLists(front_half);
        h2 = mergeKLists(back_half);
        return merge(h1,h2);
    }
      
      
      
      // too slow
    ListNode* mergeKLists_SLOW(vector<ListNode*>& lists) 
    {
        if (lists.size()==0) {return NULL;}
        if (lists.size()==1) {return lists[0];}
        
        ListNode *temp;
        temp = lists[0];
        for (int j=1;j<lists.size();j++)
        { temp = merge(lists[j],temp); }
        return temp;
    }
    
    
         ListNode* merge(ListNode *l1, ListNode *l2)
      {
        if (!l1 && l2) {return l2;}
        if (l1 && !l2) {return l1;}
        if (!l1 && !l2) {return NULL;}
        
        ListNode *r1a, *r1b, *r2,initial(0);
        r1a = &initial;
        initial.next = l1;
        r1b = l1;
        r2 = l2;
    
        while (true)
        {
            ListNode *temp;
            temp = r2->next;
            if (r2->val < r1b->val)
            {
                r1a->next = r2;
                r2->next = r1b;
                r2 = temp;
                r1b = r1a->next;
            }
            else
            {
                r1a = r1b;
                r1b = r1b->next;
            }
            
            if (r2==0) {break;}
            if (r1b==0) {r1a->next = r2;break;}
        }
        return initial.next;
    };
      
           void print(ListNode *head)
      {
            ListNode *runner;
            runner = head;
            while (runner)
            {
                  cout << runner->val << '-';
                  runner = runner->next;
            }
            cout << endl;
      };     
 

};


int main()
{
      Solution s;
      
      ListNode *l1 = new ListNode(1),*runner;
      runner = l1;
      runner->next = new ListNode(101);runner = runner->next;
      runner->next = new ListNode(201);runner = runner->next;
      
      ListNode *l2 = new ListNode(2);
      runner = l2;
      runner->next = new ListNode(102);runner = runner->next;
      runner->next = new ListNode(202);runner = runner->next;
      runner->next = new ListNode(302);runner = runner->next;
      runner->next = new ListNode(402);runner = runner->next;
      runner->next = new ListNode(502);runner = runner->next;
 
      s.print(s.merge(l1,l2));
      return 0;
}