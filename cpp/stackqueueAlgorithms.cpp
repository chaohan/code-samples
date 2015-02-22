#include <iostream>
#include <stack>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/assignment.hpp>

namespace stackqueueAlgorithms
{      
      using namespace std;

      // print a stack in the order of oldest to newest element
      template <typename elementType>
      void printStack(stack<elementType> &input)
      {
            stack<elementType> cache;
            while (!input.empty())
            {
                  cache.push(input.top());
                  input.pop();
            }
            while (!cache.empty())
            {
                  cout << "|" << cache.top();
                  input.push(cache.top());
                  cache.pop();
            }
            cout << endl;
      };
      
      // 3.2 
      template <typename elementType>
      class minStack
      {
            private:
                  stack< pair<elementType,int> > mins;
                  stack<elementType> elements;
            public:
                  bool empty() { return elements.empty(); };
                  
                  int size() { return elements.size(); };
            
                  elementType top() { return elements.top(); };
                  
                  void push(elementType newElement)
                  {
                        if (mins.empty() || newElement < (mins.top()).first ) 
                        { mins.push(make_pair(newElement,1)); }
                        else
                        {
                              if (newElement == (mins.top()).first )
                              { (mins.top()).second++; }
                        }
                        elements.push(newElement);
                  };
                  
                  void pop()
                  {
                        if (elements.top() == (mins.top()).first)
                        { (mins.top()).second--; }
                        if ((mins.top()).second==0) {mins.pop();}
                        elements.pop();
                  };
                  
                  elementType min() { return (mins.top()).first; };
                  
                  void print() { printStack(elements); };
      };
      
      //3.3
      template <typename elementType>
      class pileStack
      {
            private: 
                  stack< stack<elementType> > superStack;
                  int pileSize;
                  int endPileSize;
            public:
                  pileStack(int pileSize) 
                  {
                        this->pileSize = pileSize;
                        stack<elementType> s;
                        superStack.push(s);
                        endPileSize = 0;
                  };
            
                  int getPileSize() { return pileSize; };
                  
                  bool empty() { return superStack.empty(); };
                  
                  int size() { return (superStack.size()-1)*pileSize + endPileSize; };
            
                  elementType top() { return superStack.top().top(); };
            
                  void push(elementType newElement) 
                  {
                        if (endPileSize<pileSize)
                        {
                              superStack.top().push(newElement);
                              endPileSize++;
                        }
                        else
                        {
                              stack<elementType> s;
                              superStack.push(s);
                              superStack.top().push(newElement);
                              endPileSize = 1;
                        }
                  };
            
                  void pop() 
                  {
                        superStack.top().pop();
                        endPileSize--;
                        if (superStack.top().empty()) 
                        { 
                              superStack.pop(); 
                              endPileSize = pileSize;
                        }
                  };
            
                  void popPile()
                  {
                        superStack.pop();
                        endPileSize = pileSize;
                  };
            
                  void print() 
                  {
                        stack< stack<elementType> > cache;
                        while (!superStack.empty())
                        {
                              cache.push(superStack.top());
                              superStack.pop();
                        }
                        
                        while (!cache.empty())
                        {
                              printStack(cache.top());
                              superStack.push(cache.top());
                              cache.pop();
                        }
                        cout << "--- end --- " << endl;
                  };
      };
      
      //3.4 Tower of Hanoi
      class TowerOfHanoiGame
      {
            private:
                  stack<int> sl,sc,sr;
                  int N;
            public:
                  TowerOfHanoiGame(int N)
                  {
                        this->N = N;
                        for (int j=N;j>0;j--) { sl.push(j); };
                  };
            
                  void move() {};
            
                  void print() 
                  {
                        cout << "-- Game View --" << endl;
                        printStack(sl);printStack(sc);printStack(sr);
                        cout << "--o----o----o--" << endl;
                  };
            
            
      };
      
      
};


int main()
{
      using namespace stackqueueAlgorithms;
      using namespace boost::numeric::ublas;
      
      matrix<int> input(12,1);
      input <<= 1,0,1,2,2,1,3,3,3,0,10,11;
      
      // testing minStack
      /*
      minStack<int> s;
      for (int j=0;j<input.size1();j++)
      { s.push(input(j,0)); }
      
      while (!s.empty())
      {
            cout << "current stack: ";
            s.print();
            cout << "mininum is " << s.min() << endl;
            s.pop();
      }
      */
      
      // testing pileStack
      /*
      pileStack<int> pS = pileStack<int>(4);
      for (int j=0;j<input.size1();j++)
      { pS.push(input(j,0)); }
      pS.print();
      for (int j=0;j<3;j++)
      { pS.popPile(); pS.print(); }
      */
      
      // testing Tower of Hanoi
      TowerOfHanoiGame game = TowerOfHanoiGame(4); 
      game.print();
      
      
      
      return 0;
}