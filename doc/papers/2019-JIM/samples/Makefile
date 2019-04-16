


FILES ?= $(wildcard *.inscore)
BIN   ?= parseINScore2

PFILES = $(FILES:%.inscore=parse/%.pdf)
EFILES = $(FILES:%.inscore=eval/%.pdf)
TFILES = $(FILES:%.inscore=tree/%.pdf)
OFILES = $(FILES:%.inscore=paths/%.pdf)


all:  $(PFILES) $(EFILES) $(TFILES) $(OFILES)

test: 
	echo $(FILES)

clean:
	rm -f tree/*.pdf eval/*.pdf parse/*.pdf


paths/%.dot: %.inscore
	@[ -d paths ] || mkdir paths
	$(BIN) -paths $< > $@	|| (rm $@; false)

tree/%.dot: %.inscore
	@[ -d tree ] || mkdir tree
	$(BIN) $< > $@	|| (rm $@; false)

eval/%.dot: %.inscore
	@[ -d eval ] || mkdir eval
	$(BIN) -eval $< > $@	|| (rm $@; false)

parse/%.dot: %.inscore
	@[ -d parse ] || mkdir parse
	$(BIN) -parse $< > $@	|| (rm $@; false)

%.pdf: %.dot
	dot -Tpdf -o $@ $<
