
DOC 	= OSCMsg.pdf
HTMLOPT = -show_section_numbers \
		  --image_type gif \
		  -address '<br /><a href="http://www.grame.fr/Recherche/Programmes/">Grame</a> - <a href="http://interlude.ircam.fr/">Interlude project</a> [ANR-08-CORD-010]'
TMP := tmpl2h.tex

all: $(DOC)
	
html:
	latex2html $(HTMLOPT) OSCMsg.tex

fullhtml:
	rm -f  OSCMsg/*.*
	latex2html $(HTMLOPT) OSCMsg.tex
	rail OSCMsg/images
	rm -f  OSCMsg/img*.*
	latex2html $(HTMLOPT) OSCMsg.tex
	cp OSCMsg.css OSCMsg

htmlclean:
	rm -f  OSCMsg/*.pl  OSCMsg/*.[trila]*   OSCMsg/WARNINGS
	
rsrc:
	make -C rsrc

clean:
	rm -f *.aux *.bbl *.blg *.log *.dvi *.rai *.ilg *.idx *.ind *.toc
	make htmlclean

OSCMsg.pdf : OSCMsg.rao OSCMsg.ind


%.bbl: %.bib
	pdflatex $(patsubst %.bib, %.tex, $<) 
	bibtex $(patsubst %.bib, %, $<)
	pdflatex $(patsubst %.bib, %.tex, $<) 

%.ind : %.idx
	makeindex $< 

%.aux : %.tex
	pdflatex $< 

%.rao: %.rai
	rail -i $(patsubst %.rai, %, $<)

%.rai: %.tex
	pdflatex $< 

%.pdf: %.tex
	pdflatex $< 
