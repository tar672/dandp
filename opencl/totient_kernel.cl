//Kernel source
#pragma OPENCL EXTENSION cl_khr_fp64: enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable
__kernel void totient(__global long* g_results, const int wgs) {   

  size_t i = get_global_id(0);
  size_t x, y, t;

  x = floor( (sqrt( (8*(double)i)+1)+1 )/2 )+1;

  y = x-(i-((x-1)*((x-1)+1)/2));
  
  while (y != 0) {
    t = x % y;
    x = y;
    y = t;
  }

  if(x == 1) atom_inc(&g_results[i % wgs]);
}
 //30000 = 273571773
