
BUNDLES = Score.ibundle Welcome.ibundle

all: $(BUNDLES)

clean:
	rm -f $(BUNDLES)

%.ibundle: %.inscore
	ITLBundleCreator $< -o $@ -js
