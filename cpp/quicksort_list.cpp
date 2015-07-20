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
    ListNode* sortList(ListNode* head) 
    {
          randomize(head);
          qsort(head,0);
          return head;     
    }
      
      
      // sort [front_node,back_node)
      void qsort(ListNode *front, ListNode *back)
      {
            if (!front || front==back)  {return;}
            if (front->next==back) {return;}
            ListNode *p;
            p = partition(front,back);
            //if (p) 
            //{
                  qsort(front,p);
                  qsort(p->next,back);
            //}
      };
      
      ListNode* partition(ListNode* front, ListNode *back)
      {
            if (!front) {return NULL;}
            ListNode *runner,*p;
            runner = front->next;
            p = front;
            while (runner!=back)
            {
                  if (runner->val <= front->val)
                  {
                        swap(p->next,runner);
                        p = p->next;
                  }
                  runner = runner->next;
            }
            swap(p,front);
            return p;
      };
      
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
      
      void randomize(ListNode *head)
      {
            srand( time(NULL) );
            ListNode *runner;
            runner = head;
            while (runner)
            {
                  if (rand()%2)
                  { swap(runner,head); }
                  runner = runner->next;
            }
      };
};

int main()
{
      Solution s;
      
      ListNode *p;
      ListNode *head = new ListNode(4);
      head->next = new ListNode(3);
      head->next->next = new ListNode(2);
      head->next->next->next = new ListNode(1);
      
      s.qsort(head,0);
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