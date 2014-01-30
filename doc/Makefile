
DOC 	= OSCMsg.pdf
HTMLOPT = -show_section_numbers \
		  --image_type png \
		  -local_icons \
		  -address '<br /><a href="http://www.grame.fr/Recherche/Programmes/">Grame</a> - <a href="http://inscore.sf.net/">INScore project</a>'
TMP := tmpl2h.tex

all: $(DOC)
	
html:
	make htlatex

oldhtml:
	latex2html $(HTMLOPT) OSCMsg.tex
	cp css/OSCMsg.css OSCMsg


htindex :
	tex '\def\filename{{OSCMsg}{idx}{4dx}{ind}} \input idxmake.4ht'
	makeindex -o OSCMsg.ind OSCMsg.4dx
	make htlatex

htlatex:
	-[ -d OSCMsg ] && rm -rf OSCMsg
	htlatex OSCMsg.tex "html,2,frames,index=3,info"
	mkdir OSCMsg
	mv *.html *.png  OSCMsg
	cp css/htlatex.css OSCMsg/OSCMsg.css
	open OSCMsg/OSCMsg.html

fullhtml:
	rm -f  OSCMsg/*.*
	latex2html $(HTMLOPT) OSCMsg.tex
	rail OSCMsg/images
	rm -f  OSCMsg/img*.*
	latex2html $(HTMLOPT) OSCMsg.tex
	cp css/OSCMsg.css OSCMsg

htmlclean:
	rm -f  OSCMsg/*.pl  OSCMsg/*.[trila]*   OSCMsg/WARNINGS
	
rsrc:
	make -C rsrc

clean:
	rm -f *.aux *.bbl *.blg *.log *.dvi *.rai *.ilg *.idx *.ind *.toc 
	rm -f *.4* *.out *.tmp *.xref *.idv *.lg OSCMsg.css
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
