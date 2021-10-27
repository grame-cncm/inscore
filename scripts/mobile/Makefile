
BUNDLES = Score.ibundle Welcome.ibundle Clock.ibundle Mixed-Resources.ibundle metro.ibundle
IBUNDLE = ../../build/bin/IBundle

all: $(BUNDLES)

clean:
	rm -f $(BUNDLES)

%.ibundle: %.inscore
	$(IBUNDLE) $< -o $@ -js -f
