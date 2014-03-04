#ifndef SIMPLE_H_
#define SIMPLE_H_

/*******************************************************************************
 *
 * initGPU : sets up the openCL environment for using a GPU.
 *           Note that the system may have more than one GPU in which case
 *           the one that has been pre-configured will be chosen.
 *           If anything goes wrong in the course, error messages will be 
 *           printed to stderr and the last error encountered will be returned.
 *
 ******************************************************************************/
extern cl_int initGPU ();

/*******************************************************************************
 *
 * initCPU : sets up the openCL environment for using the host machine.
 *           If anything goes wrong in the course, error messages will be 
 *           printed to stderr and the last error encountered will be returned.
 *           Note that this may go wrong as not all openCL implementations
 *           support this!
 *
 ******************************************************************************/
extern cl_int initCPU ();

/*******************************************************************************
 *
 * setupKernel : this routine prepares a kernel for execution. It takes the
 *               following arguments:
 *               - the kernel source as a string
 *               - the name of the kernel function as string
 *               - the number of arguments (must match those specified in the 
 *                 kernel source!)
 *               - followed by the actual arguments. Each argument to the kernel
 *                 results in two or three arguments to this function, depending
 *                 on whether these are pointers to float-arrays or integer values:
 *
 * legal argument sets are:
 *    FloatArr::clarg_type, num_elems::int, pointer::float *,     and
 *    IntConst::clarg_type, number::int
 *
 *               If anything goes wrong in the course, error messages will be 
 *               printed to stderr. The pointer to the fully prepared kernel
 *               will be returned.
 *
 *               Note that this function actually performs quite a few openCL
 *               tasks. It compiles the source, it allocates memory on the 
 *               device and it copies over all float arrays. If a more
 *               sophisticated behaviour is needed you may have to fall back to
 *               using openCL directly.
 *
 ******************************************************************************/

typedef enum {
  LongArr,
  IntConst
} clarg_type;

extern cl_kernel setupKernel( const char *kernel_source, char *kernel_name, int num_args, ...);

/*******************************************************************************
 *
 * runKernel : this routine executes the kernel given as first argument.
 *             The thread-space is defined through the next two arguments:
 *             <dim> identifies the dimensionality of the thread-space and
 *             <globals> is a vector of length <dim> that gives the upper 
 *             bounds for all axes. The argument <local> specifies the size
 *             of the work group size which need to have the same dimensionality
 *             as the overall range.
 *             If anything goes wrong in the course, error messages will be
 *             printed to stderr and the last error encountered will be returned.
 *
 *             Note that this function not only executes the kernel with the given
 *             range and warp-size, it also copies back *all* arguments from the
 *             kernel after the kernel's completion. If a more sophisticated
 *             behaviour is needed you may have to fall back to using openCL directly.
 *
 ******************************************************************************/

extern cl_int runKernel( cl_kernel kernel, int dim, size_t *global, size_t *local);

/*******************************************************************************
 *
 * printKernelTime : we internally measure the wallclock time that elapses
 *                   during the kernel execution on the device. This routine 
 *                   prints the findings to stdout.
 *                   Note that the measurement does not include any data 
 *                   transfer times for arguments or results! Note also, that
 *                   the only function that influences the time values is 
 *                   runKernel. It does not matter how much time elapses between
 *                   the last call to runKernel and the call to printKernelTime!
 *
 ******************************************************************************/

extern void printKernelTime();

/*******************************************************************************
 *
 * freeDevice : this routine releases all acquired ressources.
 *             If anything goes wrong in the course, error messages will be
 *             printed to stderr and the last error encountered will be returned.
 *
 ******************************************************************************/

extern cl_int freeDevice();

#endif /* SIMPLE_H_ */
