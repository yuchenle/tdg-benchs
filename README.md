# tdg-benchs
Set of benchmarks used to test the performance of taskgraph. Growing

## How to Build

### For benchmarks that do not belong to NAS
Firstly, set up the following environment variables:
	1. *OMP_PATH* (for TDG related builds)
	2. *MKL_ROOT* (for cholesky)
	3. *OPENCV_ROOT* (for hog)

Secondly, run `make` in the root folder of the current repository

### For NAS Benchmarks:
Access to the nas-omp folder and follow the instructions prompted by `make`. We 
need to specify the benchmark and the size to build. 