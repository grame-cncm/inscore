#
# 
#

MODEL := $(wildcard ../model/*.ts)
VIEW  := $(wildcard ../view/*.ts)

JS := $(patsubst ../%.ts, js/%.js, $(MODEL) $(VIEW)) 
TARGET := inscore.js

$(TARGET): $(MODEL)
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
