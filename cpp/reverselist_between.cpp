#include <iostream>
#include <set>
using namespace std;


 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};
 

      ListNode* test(ListNode* head) 
      {
            //set<string> s;
            //s.insert(head);
            cout << long(head) << endl;
            //cout << &(*head) << endl;
            return head;
      }

      ListNode* reverseBetween(ListNode* head, int m, int n) 
    {
            if (m==n) {return head;}
            if (n==2 && m==1) 
            {
                int temp = head->val;
                head->val = head->next->val;
                head->next->val = temp;
                return head;
            }
            
            ListNode *front=NULL,*runner=NULL,*mover=NULL,*newHead=NULL,*newTail=NULL;
            runner = head;
            
            if (m==2)  { front = head; }
            if (m>2) 
            {
                  for (int j=1;j<m-1;j++)
                  {      
                        runner=runner->next; 
                        front = runner;
                  }
            }
            
            if (front) { runner=runner->next; }
            newTail = runner;
            
            for (int j=0;j<n-m+1;j++)
            {
                  mover = runner;
                  runner=runner->next;
                  mover->next = newHead;
                  newHead = mover;
            }
            
            if(front) { front->next = newHead; }
            else { head = newHead; }
            
            newTail->next = runner;
            
            return head;
    }

int main()
{
      
      ListNode *head;
      ListNode first_item(1),second_item(2),third_item(3);
      first_item.next = &second_item;
      second_item.next = &third_item;
      head = &first_item;
      
      head = reverseBetween(head,2,3);
      
      cout << head->val << head->next->val << head->next->next->val << endl;
      
      
      
      //cout << result->val << endl;
      //cout << result->next << endl;
      //double x = pi();
      //printf("%.17g\n%.17g\n%.17g\n", nextafter(x, 0.0), x, nextafter(x, 1.0));
      return 0;
}