SHELL=/bin/sh
BENCHMARK=is
BENCHMARKU=IS
BENCHMARK_TASKLOOP=is_taskloop
BENCHMARKU_TASKLOOP=IS_TASKLOOP
BENCHMARK_TASKLOOP_TDG=is_taskloop_tdg
BENCHMARKU_TASKLOOP_TDG=IS_TASKLOOP_TDG

include ../config/make.def

OBJS = is.o ${COMMON}/c_print_results.o ${COMMON}/c_${RAND}.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP = is_taskloop.o ${COMMON}/c_print_results.o ${COMMON}/c_${RAND}.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP_TDG = is_taskloop_tdg.o ${COMMON}/c_print_results.o ${COMMON}/c_${RAND}.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

include ../sys/make.common

tdg: ${PROGRAM_TASKLOOP_TDG}

${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}

${PROGRAM_TASKLOOP}: config ${OBJS_TASKLOOP}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP} ${OBJS_TASKLOOP} ${C_LIB}

${PROGRAM_TASKLOOP_TDG}: config ${OBJS_TASKLOOP_TDG}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP_TDG} ${OBJS_TASKLOOP_TDG} ${C_LIB} -L${OMP_PATH}

is.o:		is.cpp npbparams.hpp
	${CCOMPILE} is.cpp

is_taskloop.o: is_taskloop.cpp npbparams.hpp
	${CCOMPILE} is_taskloop.cpp

is_taskloop_tdg.o: is_taskloop.cpp npbparams.hpp
	${CCOMPILE} is_taskloop.cpp -DTDG -fopenmp-taskgraph -o $@

clean:
	- rm -f *.o *~ 
	- rm -f npbparams.hpp core
