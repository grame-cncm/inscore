
DOC = INScore-fr.pdf INScore-en.pdf

all: $(DOC)

clean:
	rm -f *.aux *.toc *.nav *.snm *.out *.log *.pdf

force:
	touch *.tex && make

INScore-fr.pdf : INScore.tex

INScore-en.pdf : INScore.tex


%.pdf: %.tex
	pdflatex $< 

