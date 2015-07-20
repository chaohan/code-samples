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
      ListNode* insertionSortList(ListNode* head) 
      {
            ListNode *r1,*r2,*tail,*prev;
            prev = head;
            tail = 0;
            while (tail != head)
            {
                  r1 = head;
                  r2 = head->next;
                  
                  if (r2==tail) {prev = head;}
                  
                  while (r2 != tail)
                  {
                        r1 = r1->next;
                        r2 = r2->next;
                        prev = r1;
                  }
                  
                  while (r2!=0)
                  { 
                        if (r1->val >r2->val) {swap(r1,r2);}
                        r1 = r1->next;
                        r2 = r2->next;
                  } 
                  
                  tail = prev;
            }
            return head;
      }
                
      
      void swap(ListNode *a, ListNode *b)
      {
            int temp;
            temp = a->val;
            a->val = b->val;
            b->val = temp;                 
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

      ListNode *head = new ListNode(1003);
      //head->next = new ListNode(4);
      //head->next->next = new ListNode(2);
      //head->next->next->next = new ListNode(8);
      
      s.print(head);     
      head = s.insertionSortList(head);
      s.print(head);
      return 0;
}