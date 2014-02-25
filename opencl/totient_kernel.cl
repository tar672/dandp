//Kernel source
#pragma OPENCL EXTENSION cl_khr_fp64: enable
__kernel void totient(__global int* g_results, const int wgs) {   

  int i = get_global_id(0);
  int x, y, t;

  x = floor((sqrt((8*(double)i)+1)-1)/2)+1;

  y = x-(i-((x-1)*((x-1)+1)/2));
  
  while (y != 0) {
    t = x % y;
    x = y;
    y = t;
  }

  atomic_inc(&g_results[i % wgs]);
}
