#
# 
#

OUT  := GUIDOEngine.framework
DEPDATE := $(shell stat -t %Y%m%d%H%M GUIDOEngine.tgz | cut -d' ' -f 9 | sed -e 's/\"//g')


#===============================================================
GUIDOEngine : $(OUT)

$(OUT): GUIDOEngine.tgz
	tar xzf GUIDOEngine.tgz
	./localise
	touch -t $(DEPDATE) $(OUT)

#===============================================================
clean :
	rm -rf $(OUT)
