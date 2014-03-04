from pyprimes import *

m = 0
for n in range(1, 10001):
	fs = factorise(n)
	
	t = n
	for f in fs:
		t *= (1-(1/float(f[0])))
		
	m += t
  
print m
		
