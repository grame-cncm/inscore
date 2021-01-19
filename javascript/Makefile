#
# 
#

.PHONY : 

MAKE ?= make

CHECKDIR := TSCheck
TSDIR := src
GLUEDIR := glueSrc
TSLIB := $(TSDIR)/lib
GLUESRC := $(wildcard $(GLUEDIR)/*.ts)
LIBSRC := $(wildcard $(TSDIR)/*.ts)
OUT	  := $(patsubst $(TSDIR)/%.ts, $(CHECKDIR)/%.js, $(TSSRC))

MODULES     := node_modules/@grame
GUIDO       := $(MODULES)/guidolib
GUIDOLIB    := $(TSLIB)/libGUIDOEngine.d.ts lib/libGUIDOEngine.js lib/libGUIDOEngine.wasm $(TSLIB)/guidoengine.ts
GUIDOMODULE := $(GUIDOLIB:lib/%=$(GUIDO)/%)

MXML        := $(MODULES)/libmusicxml
XMLLIB      := lib/libmusicxml.js lib/libmusicxml.wasm $(TSLIB)/libmusicxml.d.ts $(TSLIB)/libmusicxml.ts
XMLMODULE   := $(XMLLIB:lib/%=$(MXML)/%)

FAUST        := $(MODULES)/libfaust
FAUSTLIB     := lib/libfaust-wasm.js lib/libfaust-wasm.wasm lib/libfaust-wasm.data
LIB  := inscoreview.js
GLUE := inscoreglue.js

WASMDIR      := ../build/lib
INSCOREWASM  := lib/libINScore.js lib/libINScore.wasm

all :
	git submodule update --init
	$(MAKE) ts
	$(MAKE) wasm

help :
	@echo "This makefile is intended to build the INScore Javascript library."
	@echo "Available targets are : "
	@echo "  all     : call the ts and wasm tagrgets (default)"
	@echo "  ts      : to build the view and glue libraries"
	@echo "  wasm    : to build the wasm library"
	@echo
	@echo "Project management: "
	@echo "  clean     : remove all outputs"
	@echo "  check     : check typescript code"
	@echo "  install   : install the required npm components"
	@echo "  modules   : install the external librairies (called by install target)"
	@echo

test:
	@echo $(GLUE)
	
#===============================================================
# building inscore ts view
#===============================================================
ts: $(LIB) $(GLUE)

$(GLUE): $(GLUESRC) $(GLUEDIR)/tsconfig.json
	cd $(GLUEDIR) && tsc

$(LIB): $(LIBSRC) $(TSLIB)/libINScore.d.ts $(TSDIR)/tsconfig.json
	cd $(TSDIR) && tsc
	
#===============================================================
# building inscore wasm library
#===============================================================
wasm: 
	$(MAKE) -C ../build/model wasm

#===============================================================
# project management
#===============================================================
install: lib
	npm install
	$(MAKE) modules

lib:
	mkdir lib

modules: $(GUIDOLIB) $(XMLLIB) $(FAUSTLIB) $(INSCOREWASM)

$(TSLIB)/libGUIDOEngine.d.ts : $(GUIDO)/libGUIDOEngine.d.ts
	cp $< $@
$(TSLIB)/guidoengine.ts:  $(GUIDO)/guidoengine.ts
	cp $< $@
$(TSLIB)/libmusicxml.ts : $(MXML)/libmusicxml.ts
	cp $< $@
$(TSLIB)/libmusicxml.d.ts : $(MXML)/libmusicxml.d.ts
	cp $< $@

lib/libINScore.js : $(WASMDIR)/libINScore.js
	cp $< $@
lib/libINScore.wasm : $(WASMDIR)/libINScore.wasm
	cp $< $@
lib/libfaust-wasm.js  : $(FAUST)/libfaust-wasm.js
	cp $< $@
lib/libfaust-wasm.wasm  : $(FAUST)/libfaust-wasm.wasm
	cp $< $@
lib/libfaust-wasm.data  : $(FAUST)/libfaust-wasm.data
	cp $< $@
lib/libGUIDOEngine.js  : $(GUIDO)/libGUIDOEngine.js
	cp $< $@
lib/libGUIDOEngine.wasm : $(GUIDO)/libGUIDOEngine.wasm
	cp $< $@
lib/libmusicxml.js : $(MXML)/libmusicxml.js
	cp $< $@
lib/libmusicxml.wasm : $(MXML)/libmusicxml.wasm
	cp $< $@

clean : 
	rm -f $(VIEW)
	rm -f $(OUT)

check: $(CHECKDIR) $(OUT)

$(CHECKDIR) :
	mkdir $(CHECKDIR)

TSOPT  := --jsx react --target es3 --lib es2015,dom --noImplicitAny  --noImplicitReturns --alwaysStrict
$(CHECKDIR)/%.js: $(TSDIR)/%.ts
	tsc $(TSOPT) -out $@ $< || rm $@

	
