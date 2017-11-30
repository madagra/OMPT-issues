# Unexepcted value of task structure value 
An incorrect value in the `value` field of `task_data` structure is obtained when reading the task associated data within an event callback. Issue details 
can be found [here](https://github.com/OpenMPToolsInterface/LLVM-openmp/issues/39).
### Requirements
* gcc compiler
* LLVM-openmp runtime with OMPT interface (code can be found [here](https://github.com/OpenMPToolsInterface/LLVM-openmp)) present in the `LD_LIBRARY_PATH`
### Usage
Run as follows
* `make`
* `env OMP_THREADS_NUM = 4 ./main.x`
