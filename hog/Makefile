CC			= clang
CCX			= clang++
OMP			= -fopenmp 
CFLAGS			= -g -O3
OPENCV_LIBS		= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_stitching -lopencv_imgcodecs -lopencv_flann
BIN			= personDetector
HOG			= hog
TDG			= -DTDG -fopenmp-taskgraph
OPENCV_L		= -L$(OPENCV_ROOT)/lib
OPENCV_I		= -I$(OPENCV_ROOT)/include
TDG_LIB			= $(OMP_PATH)

all: $(BIN)_vanilla $(BIN)_serial $(BIN)_record $(BIN)_for

$(BIN)_serial: $(BIN).cpp
	$(CC) $(CFLAGS) -c $(HOG).c
	$(CCX) $(OPENCV_I) $(CFLAGS) $^ -o $@ $(HOG).o $(OPENCV_L) $(OPENCV_LIBS)

$(BIN)_vanilla: $(BIN).cpp
	$(CC) $(CFLAGS)  $(OMP) -c $(HOG).c 
	$(CCX) $(OPENCV_I) $(CFLAGS)  $(OMP) $^ -o $@ $(HOG).o $(OPENCV_L) $(OPENCV_LIBS)

$(BIN)_record: $(BIN).cpp
	$(CC) $(CFLAGS)  $(OMP) $(TDG) -c $(HOG).c -o $(HOG)_record.o
	$(CCX) $(OPENCV_I) $(CFLAGS) $(OMP) $(TDG) -L$(TDG_LIB) $^ -o $@ $(HOG)_record.o $(OPENCV_L) $(OPENCV_LIBS)

$(BIN)_for: $(BIN).cpp
	$(CC) $(CFLAGS)  $(OMP) $(TDG) -c $(HOG)_for.c
	$(CCX) $(OPENCV_I) $(CFLAGS)  $(OMP) $^ -o $@ $(HOG)_for.o $(OPENCV_L) $(OPENCV_LIBS)

clean:
	rm -f *.o $(BIN)_vanilla $(BIN)_serial $(BIN)_record $(BIN)_for
	rm -rf dot json
