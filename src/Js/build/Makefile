#
# 
#

DEPS := ../src/model/Methods.ts
	
all : $(DEPS)
	make -C ../src/parser
	cd ../src && tsc
	
../src/model/Methods.ts: ../../inscore/model/Methods.cpp
	./methods2ts ../../inscore/model/Methods.cpp > ../src/model/Methods.ts

#===============================================================
# rules to compile a .ts 
js/%.js: ../%.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc -out $@ $< 
