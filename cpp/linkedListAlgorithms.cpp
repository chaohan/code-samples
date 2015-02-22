#include <iostream>
#include <set>
#include <stack>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/assignment.hpp>

namespace linkedListAlgorithms
{      
      using namespace std;
      
      template <typename keyType,typename valueType>
      struct Node 
      {
            Node<keyType,valueType> *right;
            Node<keyType,valueType> *left;
            keyType key;
            valueType value;
      };
      
      template <typename keyType,typename valueType>
      void printLinkedList(Node<keyType,valueType> &root)
      {
            Node<keyType,valueType> *runner = &root;
            while (runner!=0)
            {
                  cout << runner->key << "->";
                  runner=runner->right;
            }
            cout << endl;
      };

      // 2.1
      template <typename keyType,typename valueType>
      void removeDuplicate(Node<keyType,valueType> &root)
      {
            set<keyType> keySet;
            keySet.insert(root.key);
            Node<keyType,valueType> *runner;
            runner = &root;
            
            while (runner->right != 0)
            {
                  if (keySet.find(runner->right->key) != keySet.end()) //contains key
                  { runner->right = runner->right->right; }
                  else
                  { 
                        keySet.insert(runner->right->key); 
                        runner = runner->right;
                  }
            }
      };

      // 2.2
      // k=1 returns the last element 
      template <typename keyType,typename valueType>
      Node<keyType,valueType>* returnKthToLast(Node<keyType,valueType> &root,int k)
      {
            Node<keyType,valueType> *runner = &root;
            Node<keyType,valueType> *frontRunner = &root;
            
            for (int i=0;i<k;i++) 
            {
                  if (frontRunner!=0) { frontRunner = frontRunner->right; }
                  else { return NULL; }
            }
            
            while (frontRunner!=0)
            {
                  frontRunner = frontRunner->right;
                  runner = runner->right;
            }
            return runner;
      };
 
      template <typename keyType,typename valueType>
      void printKthToLast(Node<keyType,valueType> &root,int k)
      {
            cout << returnKthToLast(root,k)->key << endl;
      };

      //2.3
      // delete a node given only access to it; return true if successful, 
      // false if target is last element
      template <typename keyType,typename valueType>
      bool deleteNode(Node<keyType,valueType> &target)
      {
            if (target.right == 0) {return false;}
            target.key = target.right->key;
            target.value = target.right->value;
            target.right = target.right->right;
            return true;
      };
      
      //2.5
      Node<int,int>* add(Node<int,int> &num1, Node<int,int> &num2)
      {
            int carry = 0;
            int sum = 0;
            Node<int,int> *runner1, *runner2, *runner3, *result, *tail;
            result  = new Node<int,int>();
            runner1 = &num1;
            runner2 = &num2;
            runner3 = result;
            
            while (true)
            {     
                  sum = runner1->key + runner2->key;
                  if ( sum > 9) 
                  { runner3->key = (sum % 10)+ carry; carry = 1; }
                  else 
                  { runner3->key = sum+carry; carry = 0; }
                  runner2 = runner2->right;
                  runner1 = runner1->right;
                  if (runner1==0 || runner2==0) {break;}
                  else
                  {
                        runner3->right = new Node<int,int>();
                        runner3 = runner3->right;
                  }
            }
            if (runner1==0 && runner2==0 && carry==1)
            {
                  runner3->right = new Node<int,int>();
                  runner3 = runner3->right;
                  runner3->key = carry;
            }
            
            tail = max(runner1,runner2);
            if (tail!=0)
            { runner3->right = tail; runner3->key += carry; }
            
            return result;
      };
      
      
      //2.7
      // slow runner fast runner
      template <typename keyType,typename valueType>
      bool isPalindrome(Node<keyType,valueType> &head)
      {
            Node<keyType,valueType> *slowRunner,*fastRunner;
            slowRunner = &head;
            fastRunner = &head;
            bool result = true;
            stack<keyType> keyStack;
            
            while (fastRunner!=0 && fastRunner->right !=0)
            {
                  keyStack.push(slowRunner->key);
                  slowRunner = slowRunner->right;
                  fastRunner = fastRunner->right->right;
            }
            
            if (fastRunner!=0) // odd number of elements
            {  slowRunner = slowRunner->right; }
            
            while (slowRunner!=0)
            {
                  result = result && (slowRunner->key == keyStack.top());
                  keyStack.pop();
                  slowRunner = slowRunner->right;
            }
            
            return result;
      };
};


int main()
{
      using namespace linkedListAlgorithms;
      using namespace boost::numeric::ublas;
      
      matrix<int> entries(13,1);
      entries <<= 0,1,2,3,4,4,5,4,4,3,2,1,0;
      
      Node<int,int> root = {0,0,entries(0,0),0};
      Node<int,int> *runner = &root; 
      for (int i=1;i<entries.size1();i++)
      {
            runner->right = new Node<int,int>(); 
            runner->right->key = entries(i,0);
            runner = runner->right;
      }
      
      Node<int,int> root1 = {0,0,9,0};
      runner = &root1; 
      for (int i=2;i<10;i++)
      {
            runner->right = new Node<int,int>(); 
            runner->right->key = rand()%10;
            runner = runner->right;
      }
      
      printLinkedList(root);
      //printLinkedList(root1);
      //removeDuplicate(root);
      //printLinkedList(root);
      //printKthToLast(root,3);
      // runner = returnKthToLast(root,8);
      //if (deleteNode(*runner)) { printLinkedList(root); } 
      //printLinkedList(*add(root,root1));
      cout << isPalindrome<int>(root) << endl;
      return 0;
}