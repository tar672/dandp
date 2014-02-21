//Kernel source

void totient(long* ns, long* ts, long* results) {   

  int g = 3;
  
  long x, y, t;
  x = ns[g];
  y = ts[g];

  while (y != 0) {
    t = x % y;
    x = y;
    y = t;
  }
  if(x == 1) results[g] = 1;
}


void main(){}
