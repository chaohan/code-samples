import numpy as np; from numpy import *
from copy import *
import matplotlib.pyplot as pyplot, matplotlib.pylab as pylab
from matplotlib.pyplot import *
from matplotlib.pylab import *

M = lambda p,dim: np.random.rand(dim,dim)<p #.astype(int)
""" <dim x dim boolean matrix> construct the system with percolation probability 'p' """

def union(M):
      """ <dim x dim int matrix> quick-union all open sites that are connected 
      to ones in the top row """
      full = np.zeros((len(M),len(M)),dtype=bool)
      full[0] = M[0]
      def fill(j):
            """ fill j'th row, order: down/right/left/up """
            full[j+1]   = np.logical_or(full[j+1],  np.logical_and(full[j],M[j+1]))
            full[:,j+1] = np.logical_or(full[:,j+1],np.logical_and(full[:,j],M[:,j+1]))
            full[:,j]   = np.logical_or(full[:,j],  np.logical_and(full[:,j+1],M[:,j]))
            full[j]     = np.logical_or(full[j],    np.logical_and(full[j+1],M[j]))
      while True:
            full_old = deepcopy(full)
            map(fill,range(len(M)-1))
            if np.array_equal(full,full_old): break
      return M.astype(int)+full.astype(int)

def isPercolated(M):
      return (2 in M[-1])

def plot(M,filename=''):
      matshow(M,cmap='RdGy_r')#cm.gray
      xticks(np.arange(len(M))-0.5,[])
      yticks(np.arange(len(M))-0.5,[])
      grid()
      if isPercolated(M): title('percolated!')
      else: title('yeah... no...')
      if bool(filename):
            savefig(filename);clf()
      else: show()

def perc_prob(p,dim=40,Ntrial=100):
      trials = np.array([isPercolated(M(p,dim)) for j in range(Ntrial)]).astype(int)
      return float(np.count_nonzero(trials))/float(Ntrial)

def plot_perc_prob(dim=40,Ntrial=100,filename=''):
      xout = np.arange(0.5,0.7,0.001)
      yout = []
      for j in range(len(xout)):
            yout.append(perc_prob(xout[j],dim=dim,Ntrial=Ntrial))
            print 100.0*float(j)/float(len(xout)),'% done'
      pyplot.plot(xout,yout,'ro-')
      if bool(filename):
            savefig(filename);clf()
      else: show()
