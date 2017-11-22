# OMPT-task_info
This test program is intended as reproducer for an issue in OMP Tools (OMPT) interface.
An incorrect value in the `value` field of `task_data` structure is obtained when reading the task associated data within an event callback.
### Requirements
* gcc compiler
* LLVM-openmp runtime with OMPT interface (https://github.com/OpenMPToolsInterface/LLVM-openmp) present in the `LD_LIBRARY_PATH`
### Usage
Run as follows
* `make`
* `env OMP_THREADS_NUM = 4 ./main.x`
