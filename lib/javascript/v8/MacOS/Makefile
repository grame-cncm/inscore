# 
# makefile to build a 32/64 v8 library
#
# [2012-04-10] adapted to v8/gyp
#

V8 = $(HOME)/src/v8/git

V832 = $(V8)/out/ia32.release/libv8_base.ia32.a
V864 = $(V8)/out/x64.release/libv8_base.x64.a

help:
	@echo This makefile is intended to build v8 and to combine 32 bits and 64 bits architectures
	@echo in a universal binary library.
	@echo Targets are:
	@echo "       v32 : builds the a 32 bits architecture libv8.a"
	@echo "       v64 : builds the a 64 bits architecture libv8.a"
	@echo "       lib : combines 32 and 64 bits architectures in libv8.a"

lib : libv8.a

v32 : $(V832)
v64 : $(V864)

libv8.a :  $(V832) $(V864)
	libtool -o libv8.a $(V832) $(V8)/out/ia32.release/libv8_snapshot.a $(V864) $(V8)/out/x64.release/libv8_snapshot.a

$(V832) :
	cd $(V8) && make ia32.release

$(V864) :
	cd $(V8) && make x64.release

clean:
	rm -f libv8*
