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
      // cut, reverse, merge
      void reorderList(ListNode* head) 
      {
            merge_alt(head,reverseList(cuthalf(head)));
      }
      
      ListNode* cuthalf(ListNode *head)
      {
            ListNode *r1,*r2;
            r1 = head;
            r2 = head;
            while (r2 && r2->next)
            {
                  r1 = r1->next;
                  r2 = r2->next->next;
            }
            r2 = r1;
            r1 = r1->next;
            r2->next =0;
            return r1;
      }
      
      
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
      }
      
      // assuming l2 is strictly shorter than l1
      void merge_alt(ListNode *l1, ListNode *l2)
      {
            ListNode *r1, *r2;
            r1 = l1;
            r2 = l2;
            
            while (r2)
            {
                  ListNode *temp;
                  temp = r2->next;
                  r2->next = r1->next;
                  r1->next = r2;
                  
                  r1 = r2->next;
                  r2 = temp;
            }
      }
      
      
      
      
      // O(N^2) too slow
      void reorderList_SLOW(ListNode* head) 
      {
            if (!head || !head->next || !head->next->next) {return;}
            
            ListNode *r1,*r2;
            r1 = head;
            r2 = head;
            
            while (true)
            {
                  if (r1->next==0) {break;} 
                  if (r1->next->next==0) {break;}
                  
                  while (r2->next->next)
                  {r2 = r2->next;}
            
                  r2->next->next = r1->next;
                  r1->next = r2->next;
                  
                  r2->next = 0;
                  r1 = r1->next->next;
                  r2 = r1;
            }
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
      runner->next = new ListNode(2);runner = runner->next;
      runner->next = new ListNode(3);runner = runner->next;
      runner->next = new ListNode(4);runner = runner->next;
      runner->next = new ListNode(5);runner = runner->next;
      runner->next = new ListNode(6);runner = runner->next;
      
      
      
      s.print(head);     
      s.reorderList(head);
      s.print(head);
      return 0;
}