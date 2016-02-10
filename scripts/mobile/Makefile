
BUNDLES = Score.ibundle Welcome.ibundle Clock.ibundle

all: $(BUNDLES)

clean:
	rm -f $(BUNDLES)

%.ibundle: %.inscore
	IBundle $< -o $@ -js -f
