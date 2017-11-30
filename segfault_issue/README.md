# Segfault issue with idle and sync_region callbacks
These test programs are intended as reproducers for a segfault issue in the
LLVM OpenMP runtime concerning the implementation of the OMP Tools (OMPT)
interface.  When calling the `ompt_get_task_info` routine from the OMPT
interface near the end of the program execution to get informations, the
`task_data` parameter returned by this routine is freed by the OpenMP runtime
before the end of the execution of OMPT callbacks and becomes invalid, causing
segfaults in callbacks when attempting to access it.  These test programs
reproduces the segfault for `sync_region_wait` and `idle` events. Issue details
can be found [here](https://github.com/OpenMPToolsInterface/LLVM-openmp/issues/41).
### Requirements
* gcc compiler
* LLVM-openmp runtime with OMPT interface (code can be found [here](https://github.com/OpenMPToolsInterface/LLVM-openmp)) present in the `LD_LIBRARY_PATH`
### Usage
Run as follows on each subdirectory (idle and sync_region_wait)
* `make`
* `env OMP_THREADS_NUM = 4 ./main.x`
