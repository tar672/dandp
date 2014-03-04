//Kernel source
#pragma OPENCL EXTENSION cl_khr_fp64: enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable
__kernel void totient(__global long* g_results, const int wgs) {   

  long i = get_global_id(0);
  long x, y, t, max, j;
  
  for(j = 0, max = 0; max <= i; j ++) {
    x = j;
    max = (j*(j-1))/2;
  }

  y = x-(i-((x-1)*x)/2);
  
  while (y != 0) {
    t = x % y;
    x = y;
    y = t;
  }

  if(x == 1) atomic_inc(&g_results[i % wgs]);

}
