#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/assignment.hpp>

namespace stackqueueAlgorithms
{      
      using namespace std;

      /*  print a stack in from bottom to top */
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
      
      /* 3.2 
            a stack class with O(1) return time for the minimum element
      */
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
      
      /*3.3
            a conventional stack, but as a stack of "piles" 
            which are sub-stacks that can also be poped.
      */
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
      
      /*3.5
            a queue implemented using two stacks 
       */
      template <typename elementType>
      class dsQueue
      {
            private:
                  stack<elementType> ls,rs;
            
                  void move(bool print)
                  {
                        stack<elementType> *fs,*es;
                        if (ls.empty()) { es = &ls; fs = &rs; }
                        else { es = &rs; fs = &ls; }
                        
                        while (!fs->empty())
                        {
                              elementType e = fs->top();
                              es->push(e); fs->pop(); 
                              if (print) { cout << e << "<"; }
                        }
                        if (print) { cout << endl; }
                  };
            
                  bool L() {return rs.empty() && !ls.empty();}
                  bool R() {return ls.empty() && !rs.empty();}
            
            public:
                  bool empty() { return ls.empty() && rs.empty() ;};
                  
                  int size() {return ls.size() + rs.size(); };
                  
                  void push(elementType newElement) 
                  {
                        if (this->R()) { this->move(false); }
                        ls.push(newElement);
                  };
            
                  void pop() 
                  {
                        if (this->L()) { this->move(false); }
                        if (!this->empty()) { rs.pop(); }
                  };
            
                  elementType front() 
                  {
                        if (this->L()) { this->move(false); }
                        return rs.top();
                  };
            
                  elementType back()
                  {
                        if (this->R()) { this->move(false); }
                        return ls.top();
                  };
            
                  void print()
                  {
                        if (this->L()) { this->move(false); }
                        this->move(true);
                  };
      };
      
      /* 3.6
            an insertion-sort type sorting method ( O(N^2) )
            for a stack using another stack of the same size
      */
      template <typename elementType>
      void slowSort(stack<elementType> &s)
      {
            stack<elementType> cache;
            stack<elementType> *si,*sf,*temp;
            int iter = 0;
            int totalLength;
            
            while (!s.empty()) { cache.push(s.top()); s.pop(); iter++; }
            totalLength = iter;
            
            si = &cache; sf = &s; 
            while (iter!=0)
            {
                  si->push( filterMove(iter,(totalLength-iter)%2!=0,si,sf) );
                  temp = si; si = sf; sf = temp;
                  iter--;
            }
            
           while (!cache.empty()) { s.push(cache.top()); cache.pop(); }
      }
      
      // move N elements from si to sf, while taking out the 
      // min (max) if "min" = true (false)
      template <typename elementType>
      elementType filterMove(int N, bool min, stack<elementType> *si, stack<elementType> *sf)
      {
            elementType e,t;
            e = si->top(); si->pop();
            for (int j=0;j<N-1;j++) 
            {
                  t = si->top();
                  if ( (min && t<e) || (!min && t>e) ) { sf->push(e); e=t; }
                  else { sf->push(t); }
                  si->pop();
            }
            return e;
      };      
      
      /*
            print the last K lines of a file in a single run
            all lines returned if there're fewer than K lines
      */
      void printLastKLines(int K, char* filename)
      {
            ifstream file(filename);
            string line;
            queue<string> q;
            int count = 0;
            
            if (file.is_open())
            {
                  while (getline(file,line))
                  {
                        q.push(line);
                        count++;
                        if (count>K) { q.pop(); }
                  }         
                  file.close();
            }
            
            while(!q.empty())
            {
                  cout << q.front() << endl;
                  q.pop();
            }
            cout << "total line count: " << count << endl;
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
      
      // testing dsQueue
      /*
      dsQueue<int> dsq;
      for (int j=0;j<input.size1();j++)
      { dsq.push(input(j,0)); }
      while (!dsq.empty())
      { 
            cout << "size= " << dsq.size() << endl;
            dsq.print();
            dsq.pop(); 
      } 
      */
      
      // testing slowSort
      /*
      stack<int> s;
      for (int j=0;j<input.size1();j++)
      { s.push(input(j,0)); }
      printStack(s);
      slowSort(s);
      printStack(s);
      */
      
      // testing printLastKLines()
      char filename[] = "data.txt";
      printLastKLines(4,filename);
      
      
      
      return 0;
}