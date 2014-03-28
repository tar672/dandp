//Kernel source
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable
__kernel void totient(__global long* g_results, const int wgs) {   

  size_t i = get_global_id(0);
  size_t x, y, t, max, j;
  
  for(j = 10000, max = (j*(j-1))/2; max > i; j --) {
    x = j + 1;
    max = (j*(j-1))/2;
  }


  y = x-(i-((x-1)*x)/2);
  
  while (y != 0) {
    t = x % y;
    x = y;
    y = t;
  }

  if(x == 1) atom_inc(&g_results[i % wgs]);

}
