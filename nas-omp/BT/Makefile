SHELL=/bin/sh
BENCHMARK=bt
BENCHMARKU=BT

BENCHMARK_TASKLOOP=bt_taskloop
BENCHMARKU_TASKLOOP=BT_TASKLOOP

BENCHMARK_TASKLOOP_TDG=bt_taskloop_tdg
BENCHMARKU_TASKLOOP_TDG=BT_TASKLOOP_TDG

include ../config/make.def

OBJS =	bt.o \
	${COMMON}/c_print_results.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP =	bt_taskloop.o \
	${COMMON}/c_print_results.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP_TDG =	bt_taskloop_tdg.o \
	${COMMON}/c_print_results.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

include ../sys/make.common

tdg: ${PROGRAM_TASKLOOP_TDG}

${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}

${PROGRAM_TASKLOOP}: config ${OBJS_TASKLOOP}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP} ${OBJS_TASKLOOP} ${C_LIB}

${PROGRAM_TASKLOOP_TDG}: config ${OBJS_TASKLOOP_TDG}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP_TDG} ${OBJS_TASKLOOP_TDG} ${C_LIB} -L${OMP_PATH} -g

bt.o:             bt.cpp npbparams.hpp
	${CCOMPILE} bt.cpp

bt_taskloop.o:             bt_taskloop.cpp npbparams.hpp
	${CCOMPILE} bt_taskloop.cpp

bt_taskloop_tdg.o:             bt_taskloop.cpp npbparams.hpp
	${CCOMPILE} bt_taskloop.cpp -DTDG -o $@ -fopenmp-taskgraph  -g

clean:
	- rm -f *.o *~ mputil*
	- rm -f  npbparams.hpp core
