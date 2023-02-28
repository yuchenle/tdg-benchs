CC = clang
OMP = -fopenmp
LIBS = -lmkl_sequential -lmkl_core -lm -lmkl_rt -lpthread
CFLAGS = -O3 -g
BIN = cholesky
TDG = -DTDG -fopenmp-taskgraph
TDG_LIB = $(OMP_PATH)
MKL_LIB = $(MKL_ROOT)/lib/intel64
MKL_INC = $(MKL_ROOT)/include
#/apps/INTEL/oneapi/2021.3/mkl/2021.3.0/lib/intel64
all: $(BIN)_vanilla $(BIN)_serial $(BIN)_record $(BIN)_for

$(BIN)_serial: $(BIN).c
	$(CC) $(CFLAGS) -I$(MKL_INC) $^ -DSEQ -o $@ -L$(MKL_LIB) $(LIBS) 

$(BIN)_record: $(BIN).c
	$(CC) $(CFLAGS) -I$(MKL_INC) $(OMP) $(TDG) $^ -o $@ -L$(MKL_LIB) -L$(TDG_LIB) $(LIBS)

$(BIN)_vanilla: $(BIN).c
	$(CC) $(CFLAGS) -I$(MKL_INC) $(OMP) $^ -o $@ -L$(MKL_LIB) $(LIBS)

$(BIN)_for: $(BIN)_for.c
	$(CC) $(CFLAGS) -I$(MKL_INC) $(OMP) $^ -o $@ -L$(MKL_LIB) $(LIBS)

clean:
	rm -f *.o $(BIN)_serial $(BIN)_record $(BIN)_vanilla  safetycc_cholesky.c $(BIN)_for

