
# fetch the version number directly in the .pro file
VERSION := $(shell grep '^VERSION' ../../build/library.pro | sed -e 's/[^0-9.]*//g')
ALL = ALL-$(VERSION)
LIB = INScore-$(VERSION)
	
doc: lib all

lib:
	doxygen Doxylib
	-[ -d  $(LIB) ] && rm -rf $(LIB)
	mkdir $(LIB)
	mv libhtml $(LIB)/html

all:
	doxygen Doxyall
	-[ -d  $(ALL) ] && rm -rf $(ALL)
	mkdir $(ALL)
	mv allhtml $(ALL)/html

pdf:
	make -C liblatex
	mv liblatex/refman.pdf $(LIB)/$(LIB).pdf
	make -C alllatex
	mv alllatex/refman.pdf $(ALL)/$(ALL).pdf

clean:
	rm -rf libhtml liblatex allhtml alllatex *.pdf
