
# fetch the version number directly in the cmake conf file
VERSION = $(shell grep 'set .INSFWKVERS' ../../cmake/CMakeLists.txt | sed -e 's/[^0-9.]//g')
ALL = ALL-$(VERSION)
LIB = IASL-$(VERSION)
	
doc: lib all

lib:
	doxygen Doxylib
	-[ -d  $(LIB) ] && rm -rf $(LIB)
	mkdir $(LIB)
	cp -R libhtml $(LIB)/html

all:
	doxygen Doxyall
	-[ -d  $(ALL) ] && rm -rf $(ALL)
	mkdir $(ALL)
	cp -R allhtml $(ALL)/html

pdf:
	make -C liblatex
	mv liblatex/refman.pdf $(LIB)/$(LIB).pdf
	make -C alllatex
	mv alllatex/refman.pdf $(ALL)/$(ALL).pdf

clean:
	rm -rf libhtml liblatex allhtml alllatex *.pdf
