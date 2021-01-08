
SRC := $(wildcard *.rail)
OUT := $(SRC:%.rail=%.html)

all: $(OUT)

#########################################################################
# generic rule rule for html output
%.html: %.rail
	cat rail2htmlhead.html > $@ 
	rail2js $<  >> $@ 
	echo '</script> </div> </body> </html>' >> $@
	open $@
	
clean:
	rm $(OUT)