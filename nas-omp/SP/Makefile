SHELL=/bin/sh
BENCHMARK=sp
BENCHMARKU=SP

BENCHMARK_TASKLOOP=sp_taskloop
BENCHMARKU_TASKLOOP=SP_TASKLOOP

BENCHMARK_TASKLOOP_TDG=sp_taskloop_tdg
BENCHMARKU_TASKLOOP_TDG=SP_TASKLOOP_TDG

include ../config/make.def

OBJS =	sp.o \
	${COMMON}/c_print_results.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP =	sp_taskloop.o \
	${COMMON}/c_print_results.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP_TDG = sp_taskloop_tdg.o \
	${COMMON}/c_print_results.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

include ../sys/make.common

tdg: ${PROGRAM_TASKLOOP_TDG}

${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}

${PROGRAM_TASKLOOP}: config ${OBJS_TASKLOOP}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP} ${OBJS_TASKLOOP} ${C_LIB}

${PROGRAM_TASKLOOP_TDG}: config ${OBJS_TASKLOOP_TDG}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP_TDG} ${OBJS_TASKLOOP_TDG} ${C_LIB} -L${OMP_PATH} -g

sp.o:		sp.cpp npbparams.hpp
	${CCOMPILE} sp.cpp

sp_taskloop.o:		sp_taskloop.cpp npbparams.hpp
	${CCOMPILE} sp_taskloop.cpp

sp_taskloop_tdg.o:		sp_taskloop.cpp npbparams.hpp
	${CCOMPILE} sp_taskloop.cpp -DTDG -o $@ -fopenmp-taskgraph -g

clean:
	- rm -f *.o *~ mputil*
	- rm -f npbparams.hpp core
