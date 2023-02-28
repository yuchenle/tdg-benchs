# NAS-OMP

This project contains NAS-OMP folder of the NAS benchmark suite. 
NAS-OMP now also uses taskloop, except MG and IS.
Three different binaries can be built for each application, using *omp for*, *omp taskloop* and
*omp taskgraph* + *omp taskloop*.

All applications have already been modified to print the time needed to execute one iteration

## Make

* Original binaries using *omp for* and *omp taskloop*, inside the corresponding application folder, we do
	> make CLASS=S (or W, A, ...)
* Taskloop enhanced with TDG: inside the folder, we do
	> make tdg CLASS=S (or W, A, ...)

## Binaries
All binaries are located in **bin** folder

