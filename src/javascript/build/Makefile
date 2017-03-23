#
# a makefile to build inscore as a javascript library
# includes various tools
#

SRC  := $(shell find ../src -name "*.ts")
DEPS := ../src/model/Methods.ts
BUILDIR := js
OUT	 := $(patsubst ../src/%.ts, $(BUILDIR)/%.js, $(SRC))
TASKS ?= 4
	
all : ../inscore.js

help : 
	@echo "This makefile is intended to build INScore as a JavaScript library."
	@echo "Available targets are : "
	@echo "  all    : (default) build inscore.js using tsc"
	@echo "  check  : check that individual ts files are correctly compiled"
	@echo "  minify : build a minified version of inscore.js"
	@echo "  refs   : builds a dependencies graph using the reference paths for the model and the view"
	@echo "           output files are modelrefs.pdf and viewrefs.pdf (requires 'dot')"

../inscore.js : $(SRC)
	make -C ../src/parser
	cd ../src && tsc

../src/model/Methods.ts: ../../inscore/model/Methods.cpp
	./methods2ts ../../inscore/model/Methods.cpp > ../src/model/Methods.ts

check :
	rm -rf $(BUILDIR)
	make -j $(TASKS) _check

minify : ../inscore.min.js ../libGUIDOEngine.min.js

../inscore.min.js : ../inscore.js
	sh minify ../inscore

 ../libGUIDOEngine.min.js :  ../libGUIDOEngine.js
	sh minify ../libGUIDOEngine

refs: 
	make modelrefs
	make viewrefs

modelrefs: 
	./makerefs ../src/model > modelrefs.dot
	dot -Tpdf modelrefs.dot -o modelrefs.pdf

viewrefs: 
	./makerefs ../src/vhtmlview > viewrefs.dot
	dot -Tpdf viewrefs.dot -o viewrefs.pdf

allrefs: 
	./makerefs ../src > refs.dot
	dot -Tpdf refs.dot -o refs.pdf

_check : $(DEPS) $(OUT)

clean:
	rm -rf $(BUILDIR)

#===============================================================
# rules to compile a .ts 
TSOPT  := --noImplicitAny  --noImplicitReturns --alwaysStrict
JSOPTS := --allowJs  --allowUnreachableCode  --allowUnusedLabels 
#$(BUILDIR)/model/TILoader.js: ../src/model/TILoader.ts
#	@[ -d $(@D) ] || mkdir -p $(@D)
#	tsc $(JSOPTS) -out $@ $< 

#$(BUILDIR)/inscore.js: ../src/inscore.ts
#	@[ -d $(@D) ] || mkdir -p $(@D)
#	tsc $(JSOPTS) -out $@ $< 

#$(BUILDIR)/controller/IGlue.js: ../src/controller/IGlue.ts
#	@[ -d $(@D) ] || mkdir -p $(@D)
#	tsc $(JSOPTS) -out $@ $< 

#$(BUILDIR)/events/documentEvents.js: ../src/events/documentEvents.ts
#	@[ -d $(@D) ] || mkdir -p $(@D)
#	tsc $(JSOPTS)  --noImplicitReturns -out $@ $< 

$(BUILDIR)/%.js: ../src/%.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc $(TSOPT) -out $@ $< 
