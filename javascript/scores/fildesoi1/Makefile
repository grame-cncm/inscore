
WEBSRC := score.inscore controlPanel.inscore playControl.inscore help.inscore keyboard.inscore midiPanel.inscore
WEBTXT := $(WEBSRC:%=src/%.txt)

JS     := lib/libINScore.js lib/libINScore.wasm lib/FaustLibrary.js inscoreview.js inscoreglue.js
LIBS   := $(JS:%=../../%)
NAME   := FileDeSoi1


help:
	@echo "File De Soi 1 Utilities"
	@echo "Available targets are : "
	@echo "  txt        : copy required .inscore files to .inscore.txt"
	@echo "  standalone : builds a standalone version"


standalone: $(NAME)/lib $(NAME)/fonts $(NAME)/index.html
	cp $(LIBS) $(NAME)/lib
	cp -r rsrc src $(NAME)
	cp faust.* help.html fildesoi.inscore $(NAME)
	tar czf $(NAME).tgz $(NAME)
	
$(NAME)/lib:
	mkdir -p $(NAME)/lib

$(NAME)/fonts:
	cp -r ../../fonts $(NAME)

$(NAME)/index.html: index.html
	sed -e 's/script src="..\/..\//script src="/' index.html | sed -e 's/href="..\/..\//href="/' | sed -e 's/inscoreview.js/lib\/inscoreview.js/' | sed -e 's/inscoreglue.js/lib\/inscoreglue.js/' > $@

test:
	echo $(LIBS)

txt: $(WEBTXT)


src/%.inscore.txt: src/%.inscore
	cp $< $@
