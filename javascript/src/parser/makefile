
NAME = INScoreParser
RUN  = runparser.js
OUT  = $(NAME).js
SCRIPTS = ../../../../scripts

files 	= $(shell grep -v '^\#' testfiles.txt)
out    := $(patsubst $(SCRIPTS)/%.inscore, checkout/%.txt, $(files))

.PHONY: code check clean

code : $(OUT)

$(OUT) : $(NAME).l.jison $(NAME).y.jison
	jison $(NAME).y.jison $(NAME).l.jison -m commonjs

clean:
	rm -f $(OUT)

check: $(out)


checkout/%.txt: $(SCRIPTS)/%.inscore
	@[ -d $(@D) ] || mkdir -p $(@D)
	@echo "== checking $<"
	@node $(RUN) $< > $@

test: 
	@echo $(out)
