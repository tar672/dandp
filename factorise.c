/* Find out the prime factors
 * of a given number and print
 * them on the screen */
long factorize(int n)
{
  int d = 2;
  
  long t = n;
  
  if(n < 2) return;
  
  while(d < n) {
    /* if valid prime factor */
    if(n % d == 0) {
      
      t *= 1-(1/d);
      
      
      n /= d;
    }
    /* else: invalid prime factor */
    else {
      if(d == 2) d = 3;
      else d += 2;
    }
  }
   
  /* print last prime factor */
  printf("%d\n", d);
}
