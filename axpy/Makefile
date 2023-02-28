CC = clang
CFLAGS = -O3 -g
OMP = -fopenmp
TDG = -DTDG -fopenmp-taskgraph
BIN = axpy
all: $(BIN)_seq $(BIN)_vanilla $(BIN)_record $(BIN)_for
TDG_LIB = $(OMP_PATH)

$(BIN)_seq: $(BIN).c
	$(CC) $(CFLAGS) $^ -o $@

$(BIN)_vanilla: $(BIN).c
	$(CC) $(CFLAGS) $(OMP) $^ -o $@

$(BIN)_record: $(BIN).c
	$(CC) $(TDG) $(CFLAGS) $(OMP) $^ -o $@ -L$(TDG_LIB)

$(BIN)_for: $(BIN)_for.c
	$(CC) $(CFLAGS) $(OMP) $^ -o $@

clean:
	rm -f $(BIN)_seq $(BIN)_record $(BIN)_vanilla $(BIN)_for
