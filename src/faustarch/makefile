
dsp  = $(wildcard *.dsp)
GCC  = g++
OPT  = -I/usr/local/include -shared

system = $(shell uname -s)
ifeq ($(system), Darwin)
libs  = $(patsubst %.dsp, %.dylib, $(dsp))
OPT  := $(OPT) -flat_namespace
else
libs  = $(patsubst %.dsp, lib%.so, $(dsp))
OPT  := $(OPT) -fPIC
endif

all: $(libs)

clean:
	rm -f *.dsp.*

%.dylib: %.dsp
	faust -a inscore.cpp -o $<.cpp $<
	$(GCC)  $(OPT) $<.cpp -o $@

lib%.so: %.dsp
	faust -a inscore.cpp -o $<.cpp $<
	$(GCC)  $(OPT) $<.cpp -o $@
