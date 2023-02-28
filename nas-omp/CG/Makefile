SHELL=/bin/sh
BENCHMARK=cg
BENCHMARKU=CG

BENCHMARK_TASKLOOP=cg_taskloop
BENCHMARKU_TASKLOOP=CG_TASKLOOP

BENCHMARK_TASKLOOP_TDG=cg_taskloop_tdg
BENCHMARKU_TASKLOOP_TDG=CG_TASKLOOP_TDG

include ../config/make.def

OBJS = cg.o ${COMMON}/c_print_results.o  \
       ${COMMON}/c_${RAND}.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP = cg_taskloop.o ${COMMON}/c_print_results.o  \
       ${COMMON}/c_${RAND}.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

OBJS_TASKLOOP_TDG = cg_taskloop_tdg.o ${COMMON}/c_print_results.o  \
       ${COMMON}/c_${RAND}.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o

include ../sys/make.common

tdg: ${PROGRAM_TASKLOOP_TDG}
${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}

${PROGRAM_TASKLOOP}: config ${OBJS_TASKLOOP}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP} ${OBJS_TASKLOOP} ${C_LIB} -L${OMP_PATH}

${PROGRAM_TASKLOOP_TDG}: config ${OBJS_TASKLOOP_TDG}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP_TDG} ${OBJS_TASKLOOP_TDG} ${C_LIB} -L${OMP_PATH}

cg.o:             cg.cpp npbparams.hpp
	${CCOMPILE} cg.cpp

cg_taskloop.o:             cg_taskloop.cpp npbparams.hpp
	${CCOMPILE} cg_taskloop.cpp

cg_taskloop_tdg.o:             cg_taskloop.cpp npbparams.hpp
	${CCOMPILE} cg_taskloop.cpp -DTDG -fopenmp-taskgraph -o $@

clean:
	- rm -f *.o *~ 
	- rm -f npbparams.hpp core
