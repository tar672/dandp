
// TotientRance.c - Sequential Euler Totient Function (C Version)
// compile: gcc -Wall -O -o TotientRange TotientRange.c
// run:     ./TotientRange lower_num uppper_num

// Greg Michaelson 14/10/2003
// Patrick Maier   29/01/2010 [enforced ANSI C compliance]

// This program calculates the sum of the totients between a lower and an 
// upper limit using C longs. It is based on earlier work by:
// Phil Trinder, Nathan Charles, Hans-Wolfgang Loidl and Colin Runciman

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <CL/cl.h>
#include "simple.h"

#define MAX_SOURCE_SIZE (0x100000)

int main(int argc, char ** argv)
{
  long lower, upper;

  if (argc != 3) {
    printf("not 2 arguments\n");
    return 1;
  }
  sscanf(argv[1], "%ld", &lower);
  sscanf(argv[2], "%ld", &upper);
  //printf("C: Sum of Totients  between [%ld..%ld] is %ld\n",
  //lower, upper, sumTotient(lower, upper));

  long results_size = ((upper-1)*((upper-1)+1)/2);
  
  //long* ns = (long *) malloc(sizeof(long)*results_size);
  //long* ts = (long *) malloc(sizeof(long)*results_size);
  char* results = (char *) malloc(sizeof(char)*results_size);
  /*
  long i, j;
  int pos = 0;
  for(i = lower; i <= upper; i += 1){
    for(j = i-1; j > 0; j --){
      ns[pos] = i;
      ts[pos] = j;
      results[pos] = 0;
      pos += 1;
    }
  }
  
  printf("%ld\n", results_size);
  printf("%d\n", pos);
  * */
  printf("%ld\n", results_size);
  FILE *fp;
  char *KernelSource;
  size_t source_size;
  cl_kernel kernel;

  fp = fopen("totient_kernel.cl", "r");
  if (!fp) {
    fprintf(stderr, "Failed to load kernel.\n");
    exit(1);
  }
  KernelSource = (char*)malloc(MAX_SOURCE_SIZE);
  source_size = fread( KernelSource, 1, MAX_SOURCE_SIZE, fp);
  fclose( fp );
  
  size_t local[1];
  size_t global[1];
  local[0] = 100;
  global[0] = results_size;
  
  initGPU();

  // Fill in here:
  kernel = setupKernel( KernelSource, "totient", 1,
                                  //LongArr, results_size, ns,
                                  //LongArr, results_size, ts,
                                  CharArr, results_size, results);

  // Fill in here:
  runKernel( kernel, 1, global, local);

  int tot = 0;
  int l;
  for(l = 0; l < results_size; l ++)
    if(results[l] == 1) tot +=1;
  
  printf("C: Sum of Totients  between [%ld..%ld] is %d\n",
    lower, upper, tot);
  return 0;
}
