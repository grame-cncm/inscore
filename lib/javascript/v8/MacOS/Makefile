# 
# makefile to build a 32/64 v8 library
#
#

V8 = $(HOME)/src/v8

help:
	@echo This makefile is intended to build v8 and to combine 32 bits and 64 bits architectures
	@echo in a universal binary library.
	@echo Targets are:
	@echo "       v32 : builds the a 32 bits architecture libv8.a"
	@echo "       v64 : builds the a 64 bits architecture libv8.a"
	@echo "       lib : combines 32 and 64 bits architectures in libv8.a"

lib : libv8.a

v32 : libv8-32.a

v64 : libv8-64.a

libv8.a : libv8-32.a libv8-64.a
	libtool -o libv8.a libv8-32.a libv8-64.a

libv8-32.a :
	cd $(V8) && scons
	cp $(V8)/libv8.a libv8-32.a  

libv8-64.a :
	cd $(V8) && scons arch=x64
	cp $(V8)/libv8.a libv8-64.a  

clean:
	rm -f libv8*
