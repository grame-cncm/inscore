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

check : $(DEPS) $(OUT)

clean:
	rm -rf $(BUILDIR)

#===============================================================
# rules to compile a .ts 
JSOPTS := --allowJs  --allowUnreachableCode  --allowUnusedLabels
js/model/TILoader.js: ../src/model/TILoader.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc $(JSOPTS) -out $@ $< 

js/controller/IGlue.js: ../src/controller/IGlue.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc $(JSOPTS) -out $@ $< 

js/events/dragAndDrop.js: ../src/events/dragAndDrop.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc $(JSOPTS) -out $@ $< 

$(BUILDIR)/%.js: ../src/%.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc -out $@ $< 
