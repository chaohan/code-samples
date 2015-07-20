#include <iostream>
#include <vector>
using namespace std;


 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
      int count; //debug use
public:
      ListNode* sortList(ListNode* head) 
      {
            if (!head) {return head;}
            if (!head->next) {return head;}
            ListNode *mid = findMid(head);
            head = sortList(head);
            mid = sortList(mid);
            head =  merge(head,mid);
            return head;
      };
      
      ListNode* findMid(ListNode *front)
      {
            ListNode *r1,*r2,*prev;
            r1 = front;
            r2 = front;
            while(r2!=0 && r2->next!=0)
            {
                  prev = r1;
                  r1 = r1->next;
                  r2 = r2->next->next;
            }
            prev->next = 0;
            return r1;
      };
      
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

      ListNode *head = new ListNode(1003);
      head->next = new ListNode(4);
      head->next->next = new ListNode(-2);
      head->next->next->next = new ListNode(8);
      
      //ListNode *head2 = new ListNode(1);
      
      head = s.sortList(head);
      s.print(head);
      return 0;
}