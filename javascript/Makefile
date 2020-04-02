#
# 
#

.PHONY : 

MAKE ?= make

CHECKDIR := TSCheck
TSDIR := src
TSSRC := $(wildcard $(TSDIR)/*.ts)
OUT	  := $(patsubst $(TSDIR)/%.ts, $(CHECKDIR)/%.js, $(TSSRC))

MODULES     := node_modules/@grame
GUIDO       := $(MODULES)/guidolib
GUIDOLIB    := lib/libGUIDOEngine.d.ts lib/libGUIDOEngine.js lib/libGUIDOEngine.wasm src/guidoengine.ts
GUIDOMODULE := $(GUIDOLIB:lib/%=$(GUIDO)/%)

MXML        := $(MODULES)/libmusicxml
XMLLIB      := lib/libmusicxml.js lib/libmusicxml.wasm
XMLMODULE   := $(XMLLIB:lib/%=$(MXML)/%)
VIEW := inscoreview.js

all :
	$(MAKE) ts
	$(MAKE) -C emcc


help :
	@echo "This makefile is intended to build the INScore Javascript library."
	@echo "Available targets are : "
	@echo "  ts      : to build the library (default)"
	@echo
	@echo "Project management: "
	@echo "  clean     : remove all outputs"
	@echo "  check     : check typescript code"
	@echo "  install   : install the required npm components"
	@echo "  modules   : install the external librairies (called by install target)"
	@echo

test:
	@echo $(GUIDOMODULE)
	@echo $(XMLMODULE)
	
#===============================================================
# building inscore ts view
#===============================================================
ts: $(VIEW)

$(VIEW) : $(TSSRC) lib/libINScore.d.ts $(TSDIR)/tsconfig.json
	cd $(TSDIR) && tsc

#===============================================================
# project management
#===============================================================
install: 
	npm install
	$(MAKE) modules

modules: $(GUIDOLIB) $(XMLLIB)
lib/libGUIDOEngine.d.ts : $(GUIDO)/libGUIDOEngine.d.ts
	cp $< $@
lib/libGUIDOEngine.js  : $(GUIDO)/libGUIDOEngine.js
	cp $< $@
lib/libGUIDOEngine.wasm : $(GUIDO)/libGUIDOEngine.wasm
	cp $< $@
lib/libmusicxml.js : $(MXML)/libmusicxml.js
	cp $< $@
lib/libmusicxml.wasm : $(MXML)/libmusicxml.wasm
	cp $< $@
src/guidoengine.ts:  $(GUIDO)/guidoengine.ts
	sed -e 's/libGUIDOEngine.d.ts/..\/lib\/libGUIDOEngine.d.ts/'  $<  > $@

clean : 
	rm -f $(VIEW)
	rm -f $(OUT)

check: $(CHECKDIR) $(OUT)

$(CHECKDIR) :
	mkdir $(CHECKDIR)

TSOPT  := --jsx react --target es3 --lib es2015,dom --noImplicitAny  --noImplicitReturns --alwaysStrict
$(CHECKDIR)/%.js: $(TSDIR)/%.ts
	tsc $(TSOPT) -out $@ $< || rm $@

	
