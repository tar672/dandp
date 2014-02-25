//Kernel source
#pragma OPENCL EXTENSION cl_khr_fp64: enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable
__kernel void totient(__global int* g_results, const int wgs) {   

  int i = get_global_id(0);
  int x, y, t;
  
  int local_id = get_local_id(0);
  
  local int l_result[1];
  
  if(local_id == 0) l_result[0] = 0;
  
  barrier(CLK_LOCAL_MEM_FENCE);
  

  x = floor((sqrt((8*(double)i)+1)-1)/2)+1;

  y = x-(i-((x-1)*((x-1)+1)/2));
  
  while (y != 0) {
    t = x % y;
    x = y;
    y = t;
  }
  //atomic_inc(&results[i % wgs]);
  
  
  
  if(x == 1) atomic_inc(&l_result[0]);
  barrier(CLK_LOCAL_MEM_FENCE);
  
  if(local_id == 0) {
    
    atomic_add(&g_results[i %wgs], l_result[0]);
  }
}




  /* 
  
  while(x != y) {
    if(x > y) x = x-y;
    else y = y-x;
  }
  */
