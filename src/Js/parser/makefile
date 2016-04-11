
NAME = INScoreParser
OUT  = $(NAME).js

files 	= $(shell grep -v '^\#' testfiles.txt)
out    := $(patsubst ../../../scripts/%.inscore, checkout/%.txt, $(files))


code : $(OUT)

$(OUT) : $(NAME).l.jison $(NAME).y.jison
	jison $(NAME).y.jison $(NAME).l.jison

clean:
	rm -f $(OUT)

tcheck: 
	@echo $(out)

check: $(out)


checkout/%.txt: ../../../scripts/%.inscore
	@[ -d $(@D) ] || mkdir -p $(@D)
	@echo "== checking $<"
	@node $(NAME).js $< > $@
