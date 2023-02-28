SHELL=/bin/sh
BENCHMARK=ep
BENCHMARKU=EP

BENCHMARK_TASKLOOP=ep_taskloop
BENCHMARKU_TASKLOOP=EP_TASKLOOP

BENCHMARK_TASKLOOP_TDG=ep_taskloop_tdg
BENCHMARKU_TASKLOOP_TDG=EP_TASKLOOP_TDG

OMP_PATH=/home/chenle/Documents/BSC_repos/llvm/ins/lib

include ../config/make.def

OBJS = ep.o ${COMMON}/c_print_results.o ${COMMON}/c_${RAND}.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP = ep_taskloop.o ${COMMON}/c_print_results.o ${COMMON}/c_${RAND}.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP_TDG = ep_taskloop_tdg.o ${COMMON}/c_print_results.o ${COMMON}/c_${RAND}.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

include ../sys/make.common

tdg: ${PROGRAM_TASKLOOP_TDG}

${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}

${PROGRAM_TASKLOOP}: config ${OBJS_TASKLOOP}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP} ${OBJS_TASKLOOP} ${C_LIB} -L${OMP_PATH}

${PROGRAM_TASKLOOP_TDG}: config ${OBJS_TASKLOOP_TDG}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP_TDG} ${OBJS_TASKLOOP_TDG} ${C_LIB} -L${OMP_PATH}

ep.o:		ep.cpp npbparams.hpp
	${CCOMPILE} ep.cpp

ep_taskloop.o:		ep_taskloop.cpp npbparams.hpp
	${CCOMPILE} ep_taskloop.cpp

ep_taskloop_tdg.o:		ep_taskloop.cpp npbparams.hpp
	${CCOMPILE} ep_taskloop.cpp -DTDG -o $@ -fopenmp-taskgraph -g

clean:
	- rm -f *.o *~ 
	- rm -f npbparams.hpp core
