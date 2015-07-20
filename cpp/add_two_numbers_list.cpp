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
      ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
      {
            ListNode *r1,*r2,*r3,*head=new ListNode(0);
            r1 = l1;
            r2 = l2;
            r3 = head;
            int carry=0,sum,s1,s2;
            
            while (r1!=0 || r2!=0)
            {
                  s1 = (r1==0) ? 0:r1->val;
                  s2 = (r2==0) ? 0:r2->val;
                  sum = s1 + s2;
                  
                  r3->val += sum;
                  carry = r3->val/10;
                  r3->val = (r3->val)%10;
                  
                  r1 = (r1==0) ? 0:r1->next;
                  r2 = (r2==0) ? 0:r2->next;
                  r3->next = (r1==0 && r2==0 && carry==0) ? 0:new ListNode(carry);
                  r3 = r3->next;
            }
            
            return head;
      }
      
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
      
      ListNode *n1 = new ListNode(2),*runner;
      runner = n1;
      //runner->next = new ListNode(5);runner = runner->next;
      //runner->next = new ListNode();runner = runner->next;
      
      ListNode *n2 = new ListNode(9);
      runner = n2;
      runner->next = new ListNode(9);runner = runner->next;
      runner->next = new ListNode(9);runner = runner->next;
      //runner->next = new ListNode(5);runner = runner->next;
      
      s.print(s.addTwoNumbers(n1,n2));
      /*
      s.randomize(head);
      s.print(head);
      s.randomize(head);
      s.print(head);
      s.randomize(head);
      s.print(head);
      s.randomize(head);
      s.print(head);
      */
      return 0;
}