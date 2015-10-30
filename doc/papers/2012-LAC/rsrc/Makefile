
ALL = mvc.pdf OSCMsg.pdf

%.pdf: %.dot
	dot -Tpdf -o $@ $< 

all: $(ALL)

clean:
	rm -f $(ALL)

OSCMsg.pdf : OSCMsg.rao

%.aux : %.tex
	pdflatex $< 

%.rao: %.rai
	rail -i $(patsubst %.rai, %, $<)

%.rai: %.tex
	pdflatex $< 

%.pdf: %.tex
	pdflatex $< 
