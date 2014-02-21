//Kernel source
#pragma OPENCL EXTENSION cl_khr_fp64: enable
__kernel void totient(__global char* results) {   

  int i =  get_global_id(0);
  
  int x, y, t;
  x = floor((sqrt((8*(double)i)+1)-1)/2)+1;

  y = x-(i-((x-1)*((x-1)+1)/2));
  /*
  long x, y, t;
  x = ns[g];
  y = ts[g];
  */
  while (y != 0) {
    t = x % y;
    x = y;
    y = t;
  }
  if(x == 1) results[i] = (char) 1;
}
