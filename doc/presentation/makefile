
DOC = interlude-fr.pdf interlude-en.pdf

all: $(DOC)

clean:
	rm -f *.aux *.toc *.nav *.snm *.out *.log *.pdf

force:
	touch *.tex && make

interlude-fr.pdf : interlude.tex

interlude-en.pdf : interlude.tex


%.pdf: %.tex
	pdflatex $< 

