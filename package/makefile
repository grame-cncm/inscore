version := 0.60

package:= Interlude-$(version)
viewer := InterludeSceneViewer
docsrc := ../doc
docdst := ./doc
icns   := ../rsrc/ITLViewer.icns

striplist = $(shell find $(package)/$(viewer).app -name "*_debug*")

#########################
# this is for win32 only
bin    := ../cmake/release
#########################

.PHONY: doc

usage:
	@echo This makefile builds the Interlude prototype package.
	@echo It should be run on every supported platform.
	@echo usage:
	@echo "  make doc      # makes doc"
	@echo "  make macosx   # on Mac OS X"
	@echo "  make win32    # on Windows"

include makeBundle

macosx:
	[ -d $(package) ] || mkdir -p $(package)
	make -f makeInterludeBundle interludeBundle
	mv $(viewer).app $(package)/InterludeScoreViewer.app
	cp $(icns) $(package)/InterludeScoreViewer.app/Contents/Resources
	make strip
	svn export Max $(package)/Max
	rm -rf $(package)/Max/Turenas
	svn export PureData $(package)/PureData
	rm -rf $(package)/PureData/Turenas
	svn export python $(package)/python
	svn export lisp $(package)/lisp
	rm -f $(package)/lisp/ignore.txt
	cp  readme.txt $(package)
	cp  -r doc $(package)
	cd $(package)/Max/siggraph && tar xzf sigmund~.mxo.tgz && rm -f sigmund~.mxo.tgz
	chmod -x  $(shell find . -name "*.interlude")
	open $(package)/InterludeScoreViewer.app/Contents/Info.plist
		
doc: 
	[ -d $(docdst) ] || mkdir -p $(docdst)
	make -C $(docsrc)
	cp -f $(docsrc)/OSCMsg.pdf $(docdst)
	[ -d $(docdst)/html ] && rm -rf $(docdst)/html
	svn export $(docsrc)/OSCMsg $(docdst)/html
	cp -f $(docsrc)/presentation/interlude-fr.pdf $(docdst)/Interlude-fr.pdf
	cp -f $(docsrc)/presentation/interlude-en.pdf $(docdst)/Interlude-en.pdf

win32:
	[ -d $(package) ] || mkdir -p $(package)
	cp -f $(bin)/InterludeSceneViewer.exe $(package)/InterludeScoreViewer.exe
	cp -f $(bin)/*.dll $(package)
	cp -f $(bin)/guido2.ttf $(package)
	cp  -f DLLs/*.dll $(package)
	cp  readme.txt $(package)
	cp  -r doc $(package)
	cp  -r $(bin)/PlugIns $(package)

strip:
	rm -rf $(striplist)

