//Kernel source
#pragma OPENCL EXTENSION cl_khr_fp64: enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable
__kernel void totient(__global long* g_results, const int wgs) {   

  int x, y, t;
  
  x = get_global_id(0)+1;
  
  y = get_global_id(1)+1;
  
  if(y >= x) return;
  
  while (y != 0) {
    t = x % y;
    x = y;
    y = t;
  }
  
  if(x == 1) atom_inc(&g_results[y % wgs]);
  
}
 //30000 = 273571773
