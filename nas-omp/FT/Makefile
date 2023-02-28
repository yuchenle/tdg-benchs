SHELL=/bin/sh
BENCHMARK=ft
BENCHMARKU=FT

BENCHMARK_TASKLOOP=ft_taskloop
BENCHMARKU_TASKLOOP=FT_TASKLOOP

BENCHMARK_TASKLOOP_TDG=ft_taskloop_tdg
BENCHMARKU_TASKLOOP_TDG=FT_TASKLOOP_TDG

include ../config/make.def

OBJS = ft.o ${COMMON}/c_${RAND}.o ${COMMON}/c_print_results.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o #../omp-prof.o

OBJS_TASKLOOP = ft_taskloop.o ${COMMON}/c_${RAND}.o ${COMMON}/c_print_results.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o #../omp-prof.o

OBJS_TASKLOOP_TDG = ft_taskloop_tdg.o ${COMMON}/c_${RAND}.o ${COMMON}/c_print_results.o \
       ${COMMON}/c_timers.o ${COMMON}/c_wtime.o #../omp-prof.o

include ../sys/make.common

tdg: ${PROGRAM_TASKLOOP_TDG}

${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}

${PROGRAM_TASKLOOP}: config ${OBJS_TASKLOOP}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP} ${OBJS_TASKLOOP} ${C_LIB}

${PROGRAM_TASKLOOP_TDG}: config ${OBJS_TASKLOOP_TDG}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM_TASKLOOP_TDG} ${OBJS_TASKLOOP_TDG} ${C_LIB} -L${OMP_PATH}

ft.o:             ft.cpp npbparams.hpp
	${CCOMPILE} ft.cpp

ft_taskloop.o:             ft_taskloop.cpp npbparams.hpp
	${CCOMPILE} ft_taskloop.cpp

ft_taskloop_tdg.o:             ft_taskloop.cpp npbparams.hpp
	${CCOMPILE} ft_taskloop.cpp -DTDG -fopenmp-taskgraph -o $@

clean:
	- rm -f *.o *~ mputil*
	- rm -f ft npbparams.hpp core
