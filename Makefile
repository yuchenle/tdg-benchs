all:
		+$(MAKE) -C heat
		+$(MAKE) -C cholesky
		+$(MAKE) -C nbody
		+$(MAKE) -C dotp
		+$(MAKE) -C axpy
		+$(MAKE) -C hog
