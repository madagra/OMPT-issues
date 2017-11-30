# Idle event callback behavior
This test program is intended as reproducer for a possible issue in the LLVM
OpenMP runtime concerning the implementation of the OMP Tools (OMPT) interface.
The time spent by OpenMP threads (except master thread) outside parallel
regions seems to be recorded inside a `sync_region_wait` event instead of an
`idle` event. Issue details can be found [here](https://github.com/OpenMPToolsInterface/LLVM-openmp/issues/39).
### Requirements
* gcc compiler
* LLVM-openmp runtime with OMPT interface (code can be found [here](https://github.com/OpenMPToolsInterface/LLVM-openmp)) present in the `LD_LIBRARY_PATH`
### Usage
Run as follows
* `make`
* `env OMP_THREADS_NUM = 4 ./main.x`
