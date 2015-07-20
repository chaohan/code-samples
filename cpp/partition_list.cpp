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
      ListNode* partition(ListNode* head, int x)
      {
            ListNode *h1 = new ListNode(0), *h2 = new ListNode(0), *r1,*r2;
            r2 = h2;
            r1 = h1;
            h1->next = head;
            
            while (r1 && r1->next)
            {
                  if (r1->next->val < x)
                  {
                        r1 = r1->next;
                  }
                  else
                  {
                        r2->next = r1->next;
                        r1->next = r1->next->next;
                        r2 = r2->next;
                        r2->next = 0;
                  }
            }
            
            r1->next = h2->next;
            return h1->next;
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
      
      ListNode *head = new ListNode(1),*runner;
      runner = head;
      runner->next = new ListNode(4);runner = runner->next;
      runner->next = new ListNode(3);runner = runner->next;
      runner->next = new ListNode(2);runner = runner->next;
      runner->next = new ListNode(5);runner = runner->next;
      runner->next = new ListNode(2);runner = runner->next;
 
      s.print(head);
      head = s.partition(head,3);
      s.print(head);
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