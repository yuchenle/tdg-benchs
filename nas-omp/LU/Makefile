SHELL=/bin/sh
BENCHMARK=lu
BENCHMARKU=LU

BENCHMARK_TASKLOOP=lu_taskloop
BENCHMARKU_TASKLOOP=LU_TASKLOOP

BENCHMARK_TASKLOOP_TDG=lu_taskloop_tdg
BENCHMARKU_TASKLOOP_TDG=LU_TASKLOOP_TDG

include ../config/make.def

OBJS = lu.o ${COMMON}/c_print_results.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP = lu_taskloop.o ${COMMON}/c_print_results.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP_TDG = lu_taskloop_tdg.o ${COMMON}/c_print_results.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

include ../sys/make.common

tdg: ${PROGRAM_TASKLOOP_TDG}

${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}

${PROGRAM_TASKLOOP}: config ${OBJS_TASKLOOP}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP} ${OBJS_TASKLOOP} ${C_LIB}

${PROGRAM_TASKLOOP_TDG}: config ${OBJS_TASKLOOP_TDG}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP_TDG} ${OBJS_TASKLOOP_TDG} ${C_LIB} -L${OMP_PATH}

lu.o:		lu.cpp npbparams.hpp
	${CCOMPILE} lu.cpp

lu_taskloop.o:		lu_taskloop.cpp npbparams.hpp
	${CCOMPILE} lu_taskloop.cpp

lu_taskloop_tdg.o:		lu_taskloop.cpp npbparams.hpp
	${CCOMPILE} lu_taskloop.cpp -DTDG -fopenmp-taskgraph -o $@


clean:
	- /bin/rm -f npbparams.hpp
	- /bin/rm -f *.o *~
