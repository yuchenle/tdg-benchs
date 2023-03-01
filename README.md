# tdg-benchs
Set of benchmarks used to test the performance of taskgraph. Growing

## How to Build

### For benchmarks that do not belong to NAS
Firstly, set up the following environment variables (EV):
1. *OMP_PATH* : for TDG related builds, this EV needs to be set to the **TDG_INS**/lib, where **TDG_INS** is where the LLVM+Taskgraph toolchain is installed. Basically, Makefile uses this EV to correctly link the Taskgraph binaries. Otherwise, binaries using Taskgraph features will not be able to compile.
2. *MKL_ROOT*: for cholesky, this EV is specifically for Cholesky kernel. Since we call to MKL functions in it.
3. *OPENCV_ROOT*: for hog. Hog application needs OpenCV library to work, which is already comprised in its own folder. Hence, you can either set this EV to *tdg-benchs/hog/lib* or to your own opencv library folder.

Secondly, run `make` in the root folder of the current repository

### For NAS Benchmarks:
Access to the nas-omp folder and follow the instructions prompted by `make`. We 
need to specify the benchmark and the size to build. 