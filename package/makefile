version := 0.79

package:= INScore-$(version)
rsrc   := INScore-rsrc-$(version)
viewer := INScoreViewer
docsrc := ../doc
docdst := ./doc
icns   := ../rsrc/INScoreViewer.icns

rsrcf   := Max PureData python lisp
rfolders:= $(foreach dir, $(rsrcf), $(shell find $(dir) -type d))
rfiles  := $(foreach dir, $(rsrcf), $(shell find $(dir) -type f))
hfiles  := $(foreach dir, $(rsrcf), $(shell find $(dir) -name .DS_Store))
fperm   := 644  	# files permission
dperm   := 755		# folders permission

#########################
# this is for win32 only
bin    := ../cmake/release

#########################

.PHONY: doc rsrc

usage:
	@echo This makefile builds the Interlude prototype package.
	@echo It should be run on every supported platform.
	@echo usage:
	@echo "  make macosx   # on Mac OS X"
	@echo "  make win32    # on Windows"
	@echo "  make linux    # on Linux (only build the rsrc)"
	@echo "  make src      # makes src package"
	@echo "  make rsrc     # makes rsrc for SF FRS"
	@echo "  make doc      # makes doc"

include makeBundle

dmg:
	hdiutil create $(package).dmg -srcfolder $(package) -ov

macosx:
	[ -d $(package) ] || mkdir -p $(package)
	make common
	make -f makeINScoreBundle
	cp $(icns) $(viewer).app/Contents/Resources
	-[ -d $(package)/"$(viewer) $(version).app" ] && rm -rf $(package)/"$(viewer) $(version).app"
	mv $(viewer).app $(package)/"$(viewer) $(version).app"
	chmod -x  $(shell find . -name "*.inscore")
	cp -f ../src/guido2.ttf $(package)
	cd $(package) && ln -sf /Applications .
	make dmg
		
common: 
	cp -r doc $(package)
	cp readme.txt $(package)
	cp ../src/changelog.txt $(package)
		
doc: 
	make -C $(docsrc)
	make copydoc
		
copydoc: 
	[ -d $(docdst)/html ] || mkdir -p $(docdst)/html
	cp -f $(docsrc)/OSCMsg.pdf $(docdst)
	make -C $(docsrc) htmlclean
	rm -f $(docdst)/html/*
	cp  $(docsrc)/OSCMsg/* $(docdst)/html
	cp -f $(docsrc)/presentation/INScore-fr.pdf $(docdst)
	cp -f $(docsrc)/presentation/INScore-en.pdf $(docdst)

rsrc:
	make cleanrsrc
	./maketar Max $(rsrc)
	./maketar PureData $(rsrc)
	tar czf $(rsrc)/python.tgz python
	tar czf $(rsrc)/lisp.tgz lisp
	tar czf $(rsrc)/StandAlone.tgz StandAlone
	tar czf $(rsrc)/Tutorial.tgz Tutorial
	tar czf $(rsrc).tgz $(rsrc)
	mv $(rsrc).tgz $(rsrc)/all.tgz
	tar czf $(rsrc)/Max.tgz $(rsrc)/Max
	tar czf $(rsrc)/PureData.tgz $(rsrc)/PureData
	cp rsrc/cclicense.pdf $(rsrc)/license.pdf
	cp rsrc/cclicense.html $(rsrc)/license.html
	cp rsrc/whatsnew.txt $(rsrc)

cleanrsrc:
	@echo set files permission to $(fperm)
	@chmod $(fperm) $(rfiles)
	@echo set folders permission to $(dperm)
	@chmod $(dperm) $(rfolders)
	@echo remove .DS_Store
	@rm -f $(hfiles)
	rm -rf $(rsrc)/Max/* $(rsrc)/Max/PureData

src:
	[ -d $(package)-src/cmake ] || mkdir -p $(package)-src/cmake
	cp -rf ../src $(package)-src/
	cp -rf ../cmake/CMakeLists.txt $(package)-src/cmake
	cp -rf ../lib $(package)-src/
	cp readme.txt $(package)-src
	cp ../readme.txt $(package)-src/install
	cp -r doc $(package)-src
	tar czf $(package)-src.tgz $(package)-src

win32:
	[ -d $(package) ] || mkdir -p $(package)
	make common
	cp -f $(bin)/$(viewer).exe $(package)/$(viewer).exe
	cp -f $(bin)/*.dll $(package)
	cp -f ../src/guido2.ttf $(package)
	cp  -rf DLLs/* $(package)

linux:
	[ -d $(package) ] || mkdir -p $(package)
	cp -rf Max $(package)/
	cp -rf PureData $(package)
	cp -rf python $(package)
	cp -rf lisp $(package)
	cp -rf StandAlone $(package)/
	cp -rf Tutorial $(package)/
	cp readme.txt $(package)
	cp -r doc $(package)
	cp -f ../src/changelog.txt $(package)
	@echo change mode
	@chmod 644 $(shell find $(package) -type f)
	make version=$(version) -f makedeb

