# How to use
`<heat_bin> test.dat <NUM_B> <NUM_I>` where `heat_bin` is the binary to execute,
`NUM_B` the number of blocks to divide the problem into and `NUM_I` the number of iteration to simulate. 
`test.dat` is the input file to analyze.

## Test the final result
Makefile has its -DVERBOSE turned on by default, this will generate a ppm
image file at the end of each execution. Heat propagation can be seen as a propagation of red color (higher temperature) to blue canvas (cold environment). All binaries should have the same image output when taking the same input.