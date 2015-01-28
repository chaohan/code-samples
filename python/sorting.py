import sys
sys.setrecursionlimit(10000)

## ============= mergesort =============

def mergesort(data):
      aux = [0]*len(data)
      def merge(data,low,mid,high):
            ## data[low:mid+1] and data[mid+1:high] are both in order
            aux[low:high+1] = map(lambda x:x,data[low:high+1])
            i,j = low,mid+1
            for k in range(low,high+1):
                  if   i>mid : data[k] = aux[j]; j+=1
                  elif j>high: data[k] = aux[i]; i+=1
                  elif aux[j]<aux[i]: data[k] = aux[j];j+=1
                  else: data[k] = aux[i];i+=1
      
      def msort(data,low,high):
            if low >= high: return
            mid = (high+low)/2
            msort(data,low,mid)
            msort(data,mid+1,high)
            merge(data,low,mid,high)

      msort(data,0,len(data)-1)
      return data

## ============= quicksort =============

def partition(data,low,high):
      """conventional quicksort"""
      ref = data[low]
      front = low
      while low<high:
            while low<high:
                  if data[high]<ref: break
                  high -= 1
            while low<high:
                  low+=1
                  if data[low]>=ref: break
            exch(data,low,high)
      exch(data,front,low)
      return low

def partition2(data,low,high):
      """rolling first entry quicksort"""
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

