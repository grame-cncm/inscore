
BUNDLES = Score.ibundle Welcome.ibundle Clock.ibundle
IBUNDLE = ../../tools/IBundle/IBundle

all: $(BUNDLES)

clean:
	rm -f $(BUNDLES)

%.ibundle: %.inscore
	$(IBUNDLE) $< -o $@ -js -f
