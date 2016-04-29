#
# 
#

SRC  := $(shell find ../src -name "*.ts")
DEPS := ../src/model/Methods.ts
BUILDIR := js
OUT	 := $(patsubst ../src/%.ts, $(BUILDIR)/%.js, $(SRC))

	
all : $(DEPS)
	make -C ../src/parser
	cd ../src && tsc
	
../src/model/Methods.ts: ../../inscore/model/Methods.cpp
	./methods2ts ../../inscore/model/Methods.cpp > ../src/model/Methods.ts

check :
	rm -rf $(BUILDIR)
	make -j 4 _check

_check : $(DEPS) $(OUT)

clean:
	rm -rf $(BUILDIR)

#===============================================================
# rules to compile a .ts 
TSOPT  := --noImplicitAny  --noImplicitReturns
JSOPTS := --allowJs  --allowUnreachableCode  --allowUnusedLabels 
$(BUILDIR)/model/TILoader.js: ../src/model/TILoader.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc $(JSOPTS) -out $@ $< 

$(BUILDIR)/controller/IGlue.js: ../src/controller/IGlue.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc $(JSOPTS) -out $@ $< 

$(BUILDIR)/events/dragAndDrop.js: ../src/events/dragAndDrop.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc $(JSOPTS)  --noImplicitReturns -out $@ $< 

$(BUILDIR)/controller/TSetMessageHandlers.js: ../src/controller/TSetMessageHandlers.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc -out $@ $< 

$(BUILDIR)/%.js: ../src/%.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc $(TSOPT) -out $@ $< 
