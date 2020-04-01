#
# 
#

.PHONY : 

MAKE ?= make

CHECKDIR := TSCheck
TSDIR := src
TSSRC := $(wildcard $(TSDIR)/*.ts)
OUT	  := $(patsubst $(TSDIR)/%.ts, $(CHECKDIR)/%.js, $(TSSRC))

VIEW := inscoreview.js

all :
	$(MAKE) $(VIEW)
	$(MAKE) -C emcc


help :
	@echo "This makefile is intended to build the INScore Javascript library."
	@echo "Available targets are : "
	@echo "  ts      : to build the library (default)"
	@echo
	@echo "Project management: "
	@echo "  clean     : remove all outputs"
	@echo "  check     : check typescript code"
	@echo "  install   : install the required components"
	@echo

#===============================================================
# building inscore ts view
#===============================================================
ts: $(VIEW)

$(VIEW) : $(TSSRC) libINScore.d.ts $(TSDIR)/tsconfig.json
	cd $(TSDIR) && tsc

#===============================================================
# project management
#===============================================================
install:
	npm install

clean : 
	rm -f $(VIEW)
	rm -f $(OUT)

check: $(CHECKDIR) $(OUT)

$(CHECKDIR) :
	mkdir $(CHECKDIR)

TSOPT  := --jsx react --target es3 --lib es2015,dom --noImplicitAny  --noImplicitReturns --alwaysStrict
$(CHECKDIR)/%.js: $(TSDIR)/%.ts
	tsc $(TSOPT) -out $@ $< || rm $@

	
