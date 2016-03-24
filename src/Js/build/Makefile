#
# 
#

MODEL := $(wildcard ../model/*.ts)
LIB   := $(wildcard ../libraries/*/*.ts)
VIEW  := $(wildcard ../view/*.ts)

JS := $(patsubst ../%.ts, js/%.js, $(MODEL) $(VIEW) $(LIB)) 
TARGET := inscore.js

$(TARGET): $(MODEL) $(LIB)
	tsc --out inscore.js $(MODEL) 
	
all : $(JS)

#===============================================================
clean :
	rm -rf $(TARGET)

#===============================================================
# rules to compile a .ts 
js/%.js: ../%.ts
	@[ -d $(@D) ] || mkdir -p $(@D)
	tsc -out $@ $< 
