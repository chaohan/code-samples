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
 ListNode* rotateRight(ListNode* head, int k) 
    {
        if (head==0 || head->next == 0 || k==0) {return head;}
        
        head = reverseList(head); 
        
        int n = 0;
        ListNode *h2,*temp;
        h2 = head;
        
        for (int j=1;j<k;j++)
        { 
            if (h2)
            {
                  h2 = h2->next; 
                  n++;
            }
            else {break;}
        }
        
        if (h2)
        {
              temp = h2;
              h2 = h2->next;
              temp->next = NULL;
        }
        else
        {
              head = reverseList(head); 
              return rotateRight(head,k%n); 
        }
       
       
        head = reverseList(head);
        h2 = reverseList(h2); 
       
        temp = head;
        while (temp->next!=0)
        {temp = temp->next;}
        temp->next = h2;       
        
       return head;
    }
    
    
    ListNode* reverseList(ListNode* head) 
      {
            if (!head) {return head;}
            
            ListNode *runner,*mover;
            runner = head->next;
            head->next = NULL;
            
            while (runner)
            {
                  mover = runner;
                  runner=runner->next;
                  mover->next = head;
                  head = mover;
            }
            return head;
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

      ListNode *head = new ListNode(1);
      head->next = new ListNode(2);
      head->next->next = new ListNode(3);
      head->next->next->next = new ListNode(8);
      
      s.print(head);     
      head = s.rotateRight(head,6);
      s.print(head);
      return 0;
}