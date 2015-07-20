#include <iostream>
#include <cmath>
using namespace std;


 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
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
      }

int main()
{
      ListNode *head;
      ListNode first_item(1),second_item(2);
      first_item.next = &second_item;
      head = &first_item;
      
      head = reverseList(head); 
      cout << head->val << endl;
      cout << head->next->val << endl;
      
      //cout << result->val << endl;
      //cout << result->next << endl;
      //double x = pi();
      //printf("%.17g\n%.17g\n%.17g\n", nextafter(x, 0.0), x, nextafter(x, 1.0));
      return 0;
}