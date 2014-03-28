//Kernel source
#pragma OPENCL EXTENSION cl_khr_fp64: enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable
__kernel void totient(__global long* g_results, const int wgs) {   

  long i = get_global_id(0)+1;
  
  long x, y, t, yc;
  
  long tot = 0;
  
  for(yc = i; yc > 0; yc --) {
    x = i;
    y = yc;
    
    while (y != 0) {
      t = x % y;
      x = y;
      y = t;
    }
    
    if(x == 1) tot ++;
    
  }
  //atom_add(&g_results[i % wgs], tot);
}
 //30000 = 273571773

