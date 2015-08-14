import numpy as np, pandas as pd
from copy import deepcopy

__author__ = "alex han"

""" ---------------------------------------
      <<<< statistical analysis >>>> 
--------------------------------------- """

""" for arrays representing probability densities """
def normalize(input):
      """ <numpy array>: normalize the 'input' by its sum """
      return input/np.sum(input)
      
def mean_index(input):
      """ <float>: calculate the mean index value """
      return np.dot(range(len(input)),input)
      
def sigma_index(input):
      """ <float>: calculate the sigma of the index """
      mean = mean_index(input)
      return sqrt(np.dot((np.arange(len(input))-mean)**2,input))

""" for arrays representing signals """
def autocorrelate(data,Nsample):
      ## short version:
      #autocorr = map(lambda j: np.dot(data[0:Nsample],np.roll(data,-j)[0:Nsample]),range(len(data)-Nsample))
      #return abs(np.array(autocorr))      
      if Nsample>len(data): 
            print('error: sample size must be smaller than data size')
            return
      autocorr = np.zeros((len(data)-Nsample),dtype=complex)
      for j in range(len(autocorr)):
            d1 = data[0:Nsample]
            d2 = data[j:j+Nsample]
            autocorr[j] = np.vdot(d1,d2)/sqrt(np.vdot(d1,d1)*np.vdot(d2,d2))
      return abs(autocorr)

def locate_peaks(data,sorted=False):
      """<numpy array> return all (index,value) pairs of the spectral peaks in the given data,
      with the option of being sorted in descending order of data value"""
      indices = filter(lambda j: data[j]>=max([data[j-1],data[j+1]]),range(1,len(data)-1))
      result  = zip(indices,data[indices])
      if sorted:
            return np.array(sorted(result, key=lambda item:item[1], reverse=True))
      else:
            return np.array(result)


""" ---------------------------------------
            <<<< random >>>> 
---------------------------------------"""

""" diffuse a vector ('v') within a gaussian distribution, with given sigmas ('s') """
diffuse = lambda v,s: np.random.normal(loc=v,scale=abs(np.array(s))+3e-308,size=len(v))

def smear(data,Npixel):
      """ <numpy array>: return new data where every bubble of Npixel entries
      are made identical (smeared)"""
      smeared_data = deepcopy(data)
      for j in range(0,len(data),Npixel): smeared_data[j:j+Npixel] = data[j]
      return smeared_data

""" ---------------------------------------
<<<< structure generation/ generators >>>>
---------------------------------------"""

""" generate N-tuples representing grid points, from the 
input array of N 'range' arrays, for the N degrees of freedom """
ndgrid = lambda arrayOfRanges: zip(*(map(np.ravel,np.meshgrid(*arrayOfRanges))))

def enum(s,j=0):
      """ generator for enumerating through a Series, starting from the j'th entry"""
      while j<len(s):
            i = s.index[j]
            v = s.values[j]
            yield i,v
            j+=1

""" ---------------------------------------
<<<< genetic optimization algorithm >>>>
---------------------------------------"""

class genetic_optimization:
      
      def __init__(self,genesize,fitness_score,minimize=True,pplsize=50):
            """
            FITNESS_SCORE: a cutomized callable that takes a numpy array of float numbers
            in [0,1] as input and returns a measure;
            """
            self.genesize      = genesize
            self.fitness_score = fitness_score
            self.minimize      = minimize
            
            if pplsize%5:
                  self.pplsize = int((pplsize/5)*5)
                  print "population size adjusted to",self.pplsize
            else:
                  self.pplsize = pplsize
            
            self.elitesize = pplsize/5
            
            self.population = pd.DataFrame(columns=['genome','fitness'])
            
      def pplinit(self,seed=None):
            """Generate initial population. If no seed is given, random genes are provided."""
            if seed==None:
                  for j in range(1,self.pplsize+1): 
                        new_indv = self.new_indv()
                        self.population.loc[j] = [new_indv,self.fitness_score(new_indv)]
            else:
                  for j in range(1,self.pplsize+1):
                        newitem = deepcopy(seed)
                        np.random.shuffle(newitem)
                        self.population.loc[j] = [newitem,self.fitness_score(newitem)]
            self.sort_generation()
      
      def sort_generation(self):
            self.population = self.population.sort('fitness',ascending=self.minimize)
            self.population.index = np.arange(1,self.pplsize+1)
      
      def new_indv(self):
            return np.random.random(self.genesize)
      
      def generation_scores(self):
            return np.array(self.population['fitness'])
      
      def elite_flatness(self):
            elite_scores = self.generation_scores()[0:self.elitesize-2]
            return np.std(elite_scores)/np.mean(elite_scores)
            
      def evolve(self,pm1,pm2):
            ppl = self.population['genome'] 
            for j in range(1,self.elitesize+1):
                  k,l,m,n = map(lambda q: j+q*self.elitesize,[1,2,3,4])
                  ppl[k],ppl[l] = self.reproduce('s',[ppl[1],ppl[j]])
                  ppl[m],ppl[n] = self.reproduce('a',ppl[1:j+1])
            for j in range(4,self.elitesize+1):
                  self.mutate(ppl[j],pm1)
            for j in range(self.elitesize+1,self.pplsize+1):
                  self.mutate(ppl[j],pm2)

            self.population['fitness'] = np.array(map(self.fitness_score,self.population['genome']))
            self.sort_generation()
                
      def reproduce(self,label,iset):
            """ item-set has two parent genes """ 
            """gene swapping, random segmentation"""
            if label=='s':
                  j = np.random.random_integers(0,self.genesize-1)
                  #j = self.genesize/2
                  child1,child2 = map(deepcopy,iset)
                  #for j in np.random.random_integers(0,self.genesize-1,size=int(self.genesize*ps)):
                  temp = deepcopy(child1[0:j])
                  child1[0:j] = child2[0:j]
                  child2[0:j] = temp
            
            """arithmetic and geometric averaging"""
            if label=='a':
                  child1 = reduce(lambda x,y:x+y,iset)/float(len(iset))
                  child2 = reduce(lambda x,y:x*y,iset)
                  child2 = np.sign(child2) * abs(child2)**(1.0/float(len(iset)))
                  
            return child1,child2
      
      def mutate(self,indv,pm):
            """ 
            pm[0]: chance mutation happens at all
            pm[1]: percentage of the genome to be mutated
            pm[2]: percentage of gene variation from original value (mod 1)
            """
            if np.random.random()<pm[0]:
                  for j in np.random.random_integers(0,self.genesize-1,size=int(self.genesize*pm[1])):
                        indv[j] = (indv[j]*(1.0 + pm[2]*(2.0*np.random.random()-1.0))) % 1

      def bestgene(self):
            return np.array(self.population['genome'][1])

      def bestscore(self):
            return self.generation_scores()[0]
