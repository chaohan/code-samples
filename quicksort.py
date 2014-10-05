import sys
sys.setrecursionlimit(10000)

def partition(data,low,high):
      ref = data[low]
      front = low
      while low<high:
            while low<high:
                  if data[high]<ref: break
                  high -= 1
            while low<high:
                  low+=1
                  if data[low]>=ref: break
            #if low>=high: break
            exch(data,low,high)
      exch(data,front,low)
      return low

def partition2(data,low,high):
      ref = low
      far = high
      while low<high:
            if data[ref+1]<=data[ref]: exch(data,ref+1,ref); ref+=1
            else: exch(data,ref+1,far); far-=1
            if ref==far: break
      return ref

def exch(data,low,high):
      temp = data[low]; data[low] = data[high]; data[high] = temp

def qsort(data,low,high):
      if low >= high: return data
      ref = partition(data,low,high)
      qsort(data,low,ref-1)
      qsort(data,ref+1,high)
      return data

quicksort = lambda data : qsort(data,0,len(data)-1)

