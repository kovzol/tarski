##################################################################
#
# Master Makefile for QEPCAD with extensions.
#
# This simply calls qepcad's make, and the master-make for the
# extensions.
##################################################################
SHELL = /bin/bash
MAKE       =  make  # You must use gmake, but it may not be
                    # called gmake on your system, so change this

CCo        =  $(CXX)
CCd        =  $(CXX)
FLAGSo = -g -D__CORRECT_ISO_CPP_STRINGS_H_PROTO -fPIC -O3

FLAGSd = -g

ifdef STATIC
FLAGSo += -static
FLAGSd += -static
endif

ifeq ($(READLINE),0)
FLAGSo += -DNO_READLINE
FLAGSd += -DNO_READLINE
endif


SUBMAKEFLAGS = -j1

MFlags	= "CCo=${CCo}" "FLAGSo=${FLAGSo}"\
          "CCd=${CCd}" "FLAGSd=${FLAGSd}"\
          "MAKE=${MAKE}"\
	  "SUBMAKEFLAGS=${SUBMAKEFLAGS}"
MFlags += -j1

ARFLAGS := crvU
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
ARFLAGS := crv
endif

both:   opt deb

opt:
	@echo Making the optimized libraries ...
	cd extensions; ${MAKE} opt ${MFlags}
	@echo Making optimized qepcad
	cd source; ${MAKE} opt ${MFlags}

deb:
	@echo Making the debugging libraries ...
	cd extensions; ${MAKE} deb ${MFlags}
	@echo Making debugging qepcad
	cd source; ${MAKE} deb ${MFlags}

clean:	
	pushd >/dev/null source ; 'rm' -f qepcad qepcadd qepcad.a qepcadd.a ; popd >/dev/null
	pushd >/dev/null extensions ; 'rm' -f */*.a ; popd >/dev/null
	pushd >/dev/null plot2d ; 'rm' -f ADJ_2D_plot ; popd >/dev/null
	pushd >/dev/null cad2d ; 'rm' -f cad2d cad2dd cad2d.a cad2dd.a ; popd >/dev/null
	find . -name '*.o' -delete
