
def hcf(x,y):
  work = 0
  while (y != 0):
    t = x % y
    x = y
    y = t
    work += 1
  return work


def getWork(i):
  work = 0
  for j in range(1, i):
    work += hcf(i, j)

  return work


for i in range(1, 15000):
  print getWork(i)
