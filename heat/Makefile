CC 		= clang
OMP 		= -fopenmp
TDG		= -DTDG -fopenmp-taskgraph
TDG_LIB		= $(OMP_PATH)
CFLAGS = -O3 -g -DVERBOSE
LFLAGS = -lm

BIN= heat_serial heat_vanilla heat_record heat_for

all: $(BIN)

misc.o: misc.c
	$(CC) -c $(CFLAGS) $< -o $@

heat_serial: heat.c misc.o
	$(CC) $(CFLAGS) $+ $(LFLAGS) -o $@

heat_for: heat_for.c misc.o
	$(CC) $(OMP) $(CFLAGS) $+ $(LFLAGS) -o $@

heat_serial_blocked: heat.c solver.c misc.o
	$(CC) $(CFLAGS) $+ $(LFLAGS) -o $@

heat_record: heat.c misc.o
	$(CC) $(CFLAGS) $(OMP) $^ $(TDG) -o $@ $(LFLAGS) -L$(TDG_LIB)

heat_vanilla: heat.c misc.o
	$(CC) $(OMP) $(CFLAGS) $+ $(LFLAGS) -o $@ -L$(TDG_LIB)

clean:
	rm -fr *.o $(BIN) *ppm tdg.dot tdg.c *_tdg.c
