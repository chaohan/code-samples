#include <iostream>
#include <set>
using namespace std;


 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution 
{
public:
      ListNode* reverseKGroup(ListNode* head, int k) 
      {
            ListNode *h0=new ListNode(0),*r1,*r2,*temp;
            h0->next = head;
            r1 = h0;
            r2 = r1;
            
            while (r2)
            {
                  for (int j=0;j<k;j++)
                  {
                        if (r2) {r2 = r2->next;}
                        else {return h0->next;}
                  }
                  if(!r2) {return h0->next;}
                  
                  
                  temp = r2->next;
                  r2->next = 0;
                  r1->next = reverseList(r1->next);
                  while (r1->next) {r1=r1->next;}
                  r1->next= temp;
                  r2 = r1;
                  
            }
            
            return h0->next;        
      };
      
      
      ListNode* reverseList(ListNode* head) 
      {
            if (head==0) { return head; }
            if (head->next==0) { return head; }
            
            ListNode *runner,*tail;
            runner = head->next;
            tail = head;
            
            while (runner != 0)
            {
                  tail->next = runner->next;
                  runner->next = head;
                  head = runner; runner=tail->next;
            }
            
            return head;
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

      ListNode *head = new ListNode(1),*runner;
      runner = head;
      /*
      runner->next = new ListNode(2);runner = runner->next;
      runner->next = new ListNode(3);runner = runner->next;
      runner->next = new ListNode(4);runner = runner->next;
      runner->next = new ListNode(5);runner = runner->next;
      runner->next = new ListNode(6);runner = runner->next;
      */
      s.print(head);
      //head = s.reverseList(head);
      head = s.reverseKGroup(head,2);
      s.print(head);
      
      return 0;
}