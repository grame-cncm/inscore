
ROOT=../src
DEST=libmapping
INCL := $(wildcard $(ROOT)/misc/*.h $(ROOT)/parser/*.h $(ROOT)/relations/*.h $(ROOT)/segments/*.h)


help:
	@echo This makefile builds the libmapping package.
	@echo usage:
	@echo "  make headers  # collects the header files into the $(DEST) folder"

headers:
	[ -d $(DEST) ] || mkdir $(DEST)
	rm -f $(DEST)/*
	cp $(INCL) $(DEST)
	