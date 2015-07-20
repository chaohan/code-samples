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
      ListNode *detectCycle(ListNode *head) 
    {
        if (!head || !head->next) {return NULL;}
        
        ListNode *r1,*r2;
        r1 = head;
        r2 = head;
        while (true)
        {
            if (!r2 || !r2->next) {return NULL;}
            r1 = r1->next;
            r2 = r2->next->next;
            if (r1==r2) {break;}
        }
        
        r2 = head;
        while (r1!=r2)
        {r1 = r1->next;r2 = r2->next;}
        return r1;
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
      runner->next = head;
      /*
      
      runner->next = new ListNode(2);runner = runner->next;
      runner->next = new ListNode(5);runner = runner->next;
      runner->next = new ListNode(2);runner = runner->next;
      */
      //s.print(head);
      runner = s.detectCycle(head);
      bool r = runner==NULL;
      cout << runner->val << endl;
      
      return 0;
}