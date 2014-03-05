
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <CL/cl.h>
#include "simple.h"

#define MAX_SOURCE_SIZE (0x100000)

int main(int argc, char ** argv)
{
  long upper;
  int WGS;

  if (argc != 3) {
    printf("not 2 arguments\n");
    return 1;
  }
  sscanf(argv[2], "%ld", &upper);
  sscanf(argv[3], "%d", &WGS);
  
  //Calculate the number of hcf calls required
  long results_size = ((upper-1)*upper)/2;
  
  //Array for summing the totals
  long* results = (long *) malloc(sizeof(long)*WGS);
  int i;
  for(i = 0; i < WGS; i ++) results[i] = 0;

  //Read in the kernel
  FILE *fp;
  char *KernelSource;
  cl_kernel kernel;
  fp = fopen("totient_kernel.cl", "r");
  if (!fp) {
    fprintf(stderr, "Failed to load kernel.\n");
    exit(1);
  }
  KernelSource = (char*)malloc(MAX_SOURCE_SIZE);
  fread( KernelSource, 1, MAX_SOURCE_SIZE, fp);
  fclose( fp );
  
  
  //Set up and run the kernel using the simple.c functions
  size_t local[1];
  size_t global[1];
  local[0] = WGS;
  global[0] = results_size;
  
  initGPU();

  kernel = setupKernel( KernelSource, "totient", 2,
                                  LongArr, WGS, results,
                                  IntConst, WGS);

  runKernel( kernel, 1, global, local);
  
  //Sum the Totals
  long tot = 0;
  int l;
  for(l = 0; l < WGS; l ++)
    tot += results[l];
  
  printf("C: Sum of Totients between [%ld..%ld] is %ld\n",
    lower, upper, tot);
  return 0;
}
