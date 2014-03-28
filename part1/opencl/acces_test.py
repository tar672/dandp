from math import sqrt, floor

l = [1, 2, 1, 3, 2, 1, 4, 3, 2, 1, 5, 4, 3, 2, 1]

i = 5


#hcf(3, 2)

x = floor((sqrt((8*i)+1)-1)/2)+1;

print x
print x-(i - ((x-1)*((x-1)+1)/2));
