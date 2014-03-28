
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <CL/cl.h>
#include "simple.h"

#define MAX_SOURCE_SIZE (0x100000)

int main(int argc, char ** argv)
{
  long lower, upper;
  int WGS, WGS2;

  if (argc != 5) {
    printf("not 2 arguments\n");
    return 1;
  }
  sscanf(argv[1], "%ld", &lower);
  sscanf(argv[2], "%ld", &upper);
  sscanf(argv[3], "%d", &WGS);
  sscanf(argv[4], "%d", &WGS2);

  long results_size = upper;

  long* results = (long *) malloc(sizeof(long)*WGS);
  int i;
  for(i = 0; i < WGS; i ++) results[i] = 0;

  printf("%ld\n", results_size);
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
  
  size_t local[2];
  size_t global[2];
  local[0] = WGS;
  global[0] = results_size;
  
  local[1] = WGS2;
  global[1] = results_size;
  
  initGPU();

  // Fill in here:
  kernel = setupKernel( KernelSource, "totient", 2,
                                  LongArr, WGS, results,
                                  IntConst, WGS);

  // Fill in here:
  runKernel( kernel, 2, global, local);

  long tot = 0;
  int l;
  for(l = 0; l < WGS; l ++)
    tot += results[l];
  
  printf("C: Sum of Totients between [%ld..%ld] is %ld\n",
    lower, upper, tot);
  return 0;
}
