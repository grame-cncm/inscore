

ALL = addess_space.pdf mvc.pdf model.pdf update.pdf mappings.pdf localmappings.pdf


all: $(ALL)

clean:
	rm -f $(ALL)


%.pdf: %.dot
	dot -Tpdf -o $@ $< 
	cp  $@ ../imgs
