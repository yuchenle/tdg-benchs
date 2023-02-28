SHELL=/bin/sh
BENCHMARK=mg
BENCHMARKU=MG
BENCHMARK_TASKLOOP=mg_taskloop
BENCHMARKU_TASKLOOP=MG_TASKLOOP
BENCHMARK_TASKLOOP_TDG=mg_taskloop_tdg
BENCHMARKU_TASKLOOP_TDG=MG_TASKLOOP_TDG

include ../config/make.def

OBJS = mg.o ${COMMON}/c_print_results.o  \
       ${COMMON}/c_${RAND}.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP = mg_taskloop.o ${COMMON}/c_print_results.o  \
       ${COMMON}/c_${RAND}.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP_TDG = mg_taskloop_tdg.o ${COMMON}/c_print_results.o  \
       ${COMMON}/c_${RAND}.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

include ../sys/make.common

tdg: ${PROGRAM_TASKLOOP_TDG}

${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}

${PROGRAM_TASKLOOP}: config ${OBJS_TASKLOOP}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP} ${OBJS_TASKLOOP} ${C_LIB} -L${OMP_PATH}

${PROGRAM_TASKLOOP_TDG}: config ${OBJS_TASKLOOP_TDG}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP_TDG} ${OBJS_TASKLOOP_TDG} ${C_LIB} -L${OMP_PATH}

mg.o:		mg.cpp npbparams.hpp 
	${CCOMPILE} mg.cpp

mg_taskloop.o:		mg_taskloop.cpp npbparams.hpp 
	${CCOMPILE} mg_taskloop.cpp -g

mg_taskloop_tdg.o:		mg_taskloop.cpp npbparams.hpp 
	${CCOMPILE} mg_taskloop.cpp -DTDG -o $@ -fopenmp-taskgraph

clean:
	- rm -f *.o *~ 
	- rm -f npbparams.hpp core
