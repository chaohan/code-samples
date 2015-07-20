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
      ListNode* deleteDuplicates(ListNode* head) 
      {
            if (!head) {return NULL;}
        
            ListNode *runner, *prev, *h0 = new ListNode(0);
            h0->next = head;
            runner = head;
            prev = h0;
            
            while (runner!=0 && runner->next!=0)
            {
                  if (runner->val < runner->next->val)
                  {
                        prev = runner;
                        runner = runner->next;
                  }
                  else
                  {
                        
                        ListNode *temp;
                        temp = runner->next;
                        while (temp!=0 && temp->val == runner->val)
                        { temp = temp->next; }
                        prev->next = temp;
                        runner = temp;     
                  }
            }
            
            return h0->next;
        
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
      
      ///*
      ListNode *head = new ListNode(3);
      head->next = new ListNode(3);
      head->next->next = new ListNode(3);
      head->next->next->next = new ListNode(3);
      //*/
      s.print(head);
      head = s.deleteDuplicates(head);
      s.print(head);
      return 0;
}