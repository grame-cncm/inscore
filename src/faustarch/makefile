
dsp  = $(wildcard *.dsp)
libs = $(patsubst %.dsp, %.dylib, $(dsp))
GCC  = g++
OPT  = -I/usr/local/lib/faust -shared -flat_namespace

all: $(libs)

clean:
	rm -f *.dsp.*

%.dylib: %.dsp
	faust -a inscore.cpp -o $<.cpp $<
	$(GCC)  $(OPT) $<.cpp -o $@
