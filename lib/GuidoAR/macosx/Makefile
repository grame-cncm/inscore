#
# 
#

OUT  := guidoar.framework
DEPDATE := $(shell stat -t %Y%m%d%H%M guidoar.tgz | cut -d' ' -f 9 | sed -e 's/\"//g')


#===============================================================
guidoar : $(OUT)

$(OUT): guidoar.tgz
	tar xzf guidoar.tgz
	./localise
	touch -t $(DEPDATE) $(OUT)

#===============================================================
clean :
	rm -rf $(OUT)
