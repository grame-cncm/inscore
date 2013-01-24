
dsp  = $(wildcard *.dsp)
GCC  = g++
OPT  = -I/usr/local/include -I. -shared

system = $(shell uname -s)
ifeq ($(system), Darwin)
 libs  = $(patsubst %.dsp, %.dylib, $(dsp))
 OPT  := $(OPT) -flat_namespace
else
 ifeq ($(system), MINGW32_NT-6.1)
  libs  = $(patsubst %.dsp, %.dll, $(dsp))
  OPT  := $(OPT) -DINSCORE_EXPORTS
 else
  libs  = $(patsubst %.dsp, lib%.so, $(dsp))
  OPT  := $(OPT) -fPIC
 endif
endif

all: $(libs)

test:
	echo $(system)
	echo $(libs)

clean:
	rm -f *.dsp.*

%.dylib: %.dsp
	faust -a inscore.cpp -o $<.cpp $<
	$(GCC)  $(OPT) $<.cpp -o $@

lib%.so: %.dsp
	faust -a inscore.cpp -o $<.cpp $<
	$(GCC)  $(OPT) $<.cpp -o $@

%.dll: %.dsp
	echo make dll
	faust.exe -a inscore.cpp -o $<.cpp $<
	$(GCC)  $(OPT) $<.cpp -o $@
