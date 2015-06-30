version := 1.15
system	:= $(shell uname -s)
ifeq ($(system), MINGW32_NT-6.1) 
	win32 = yes
else
ifeq ($(system), CYGWIN_NT-6.1) 
	win32 = yes
endif
endif

i2i90  := ../tools/inscore2inscore90
i2i100 := ../tools/inscore2inscore100
ifeq ($(system), Darwin)
  i2i90tool  := $(i2i90)/cmake/Release/inscore2inscore90
  i2i100tool := $(i2i100)/cmake/Release/inscore2inscore100
else
ifdef win32 
  i2i90tool  := $(i2i90)/cmake/Release/inscore2inscore90.exe
  i2i100tool := $(i2i100)/cmake/Release/inscore2inscore100.exe
  QT5         := /c/Qt/Qt5.4.0
  WIN32QTPATH := $(QT5)/5.4/msvc2010_opengl/
  WIN32QT	  := QT5PRINTSUPPORT.DLL QT5WIDGETS.DLL QT5OPENGL.DLL QT5GUI.DLL QT5CORE.DLL QT5SVG.DLL QT5QML.DLL QT5WebSockets.DLL QT5Multimedia.DLL  QT5MultimediaWidgets.DLL Qt5Network.dll ICUIN53.DLL ICUUC53.DLL ICUDT53.DLL
  WIN32QT	  := $(patsubst %, $(WIN32QTPATH)/bin/%, $(WIN32QT))
  WIN32QTPLUGS     := qgif.dll qtiff.dll qjpeg.dll
  WIN32QTPLATFORMS := qminimal.dll qoffscreen.dll qwindows.dll
  WIN32QTPLUGS     := $(patsubst %, $(WIN32QTPATH)/plugins/imageformats/%, $(WIN32QTPLUGS))
  WIN32QTPLATFORMS := $(patsubst %, $(WIN32QTPATH)/plugins/platforms/%, $(WIN32QTPLATFORMS))
else
  i2i90tool  := $(i2i90)/cmake/inscore2inscore90
  i2i100tool := $(i2i100)/cmake/inscore2inscore100
endif
endif

package:= INScore-$(version)
rsrc   := INScore-rsrc-$(version)
viewer := INScoreViewer
interf := interfaces
docsrc := ../doc
docdst := ./doc

macapp  := $(viewer)-$(version).app
winapp  := $(viewer)-$(version).exe
macplug := $(macapp)/Contents/Plugins
winplug := Plugins

#########################
# scripts provided as samples are now stored in a file
scripts := $(shell cat samples-list.txt)


#########################
# this is for win32 only
bin    := ../build/win32/release

#########################

.PHONY: doc rsrc

usage:
	@echo This makefile builds the INScore package.
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

cleanperms:
	@chmod -x  $(shell find $(package) -name "*.inscore")

macosx:
	[ -d $(package) ] || mkdir -p $(package)
	make common
	make -f makeINScoreBundle
	-[ -d $(package)/$(macapp) ] && rm -rf $(package)/$(macapp)
	mv $(viewer).app $(package)/$(macapp)
	make cleanperms
	cp -f ../src/guido2.ttf $(package)
	cd $(package) && ln -sf /Applications .
	[ -d $(package)/$(macplug) ] || mkdir $(package)/$(macplug)
	cp ../lib/GestureFollower/macosx/libGFLib.dylib $(package)/$(macplug)
	cp ../lib/faust/macosx/libfaust.dylib $(package)/$(macplug)
	cp ../lib/httpserver/build/Release/libinscorehttpd.dylib $(package)/$(macplug)
	make dmg
		
common: 
	cp -r doc $(package)
	cp readme.txt $(package)
	cp ../src/changelog.txt $(package)
	make samples
		
doc: 
#	make -C $(docsrc)
	make copydoc
		
copydoc: 
	[ -d $(docdst)/html ] || mkdir -p $(docdst)/html
	cp -f $(docsrc)/OSCMsg.pdf $(docdst)
	make -C $(docsrc) htmlclean
	rm -f $(docdst)/html/*
	cp  $(docsrc)/OSCMsg/* $(docdst)/html
	cp  $(docsrc)/refcards/INScore-refcard-1.12.pdf $(docdst)
	cd  $(docdst) && tar czf html.tgz html

interfaces:
	[ -d $(rsrc)/$(interf) ] || mkdir -p $(rsrc)/$(interf)
	tar czf $(rsrc)/$(interf)/python.tgz ../$(interf)/python
	tar czf $(rsrc)/$(interf)/lisp.tgz ../$(interf)/lisp
	tar czf $(rsrc)/$(interf)/csound.tgz ../$(interf)/csound	

scripts:
	[ -d $(rsrc)/scripts ] || mkdir -p $(rsrc)/scripts
	cp -R ../scripts/Standalone/* $(rsrc)/scripts
	rm -f $(shell find $(rsrc)/scripts -name "*DS_Store")
	cd $(rsrc) && tar czf scripts.tgz scripts

patches:
	[ -d $(rsrc)/patches ] || mkdir -p $(rsrc)/patches
	cp -R ../scripts/MP-* $(rsrc)/patches
	cp -R ../scripts/M-* $(rsrc)/patches
	rm -f $(shell find $(rsrc)/patches -name "*DS_Store")
	mv $(rsrc)/patches/MP-Turenas $(rsrc)/Turenas
	cd $(rsrc) && tar czf patches.tgz patches
	cd $(rsrc) && tar czf Turenas.tgz Turenas

rsrc:
	make interfaces
	make scripts
	make patches
	cp -R ../scripts/Perception $(rsrc)
	cd $(rsrc) && tar czf Perception.tgz Perception
	cp -R ../scripts/Max-tools $(rsrc)
	cd $(rsrc) && tar czf Max-tools.tgz Max-tools
	cp -R ../scripts/PureData-tools $(rsrc)
	cd $(rsrc) && tar czf PureData-tools.tgz PureData-tools
	cp -R ../scripts/readme* $(rsrc)
	cp rsrc/cclicense.pdf $(rsrc)/license.pdf
	cp rsrc/cclicense.html $(rsrc)/license.html
	cp rsrc/whatsnew.txt $(rsrc)
	tar czf $(rsrc).tgz $(rsrc)/*[^z]

samples:
	@[ -d $(package)/samples ] || mkdir -p $(package)/samples
	rm -rf $(package)/samples/*
	@echo ========================
	@echo " copying sample scripts"
	@echo ========================
	$(foreach s,$(scripts), cp -R ../scripts/$(s) $(package)/samples/;)
	
src:
	[ -d $(package)-src ] || mkdir -p $(package)-src
	cp -rf ../src $(package)-src/
	cp -rf ../build/CMakeLists.txt $(package)-src/cmake
	cp -rf ../build/Makefile $(package)-src/cmake
	cp -rf ../build/Info.plist $(package)-src/cmake
	cp -rf ../lib $(package)-src/
	cp -rf ../win32 $(package)-src/
	rm -rf $(package)-src/lib/poppler
	rm -rf $(package)-src/lib/lua
	rm -rf $(package)-src/lib/javascript
	cp readme.txt $(package)-src
	cp ../readme.txt $(package)-src/install
	cp -r doc $(package)-src
	@echo ===================================	
	@echo manually cleanup src folder from hidden, unused and unwanted files
	@echo ===================================	
	tar czf $(package)-src.tgz $(package)-src

win32:
	[ -d $(package) ] || mkdir -p $(package)
	[ -d $(package)/plugins/imageformats ] || mkdir -p $(package)/plugins/imageformats
	[ -d $(package)/plugins/platforms ] || mkdir -p $(package)/plugins/platforms
	make common
	cp -f $(bin)/$(viewer).exe $(package)/$(viewer).exe
	cp -f $(bin)/*.dll $(package)
	cp -f ../src/guido2.ttf $(package)
	cp  $(WIN32QT) $(package)
	cp $(QT5)/vcredist/vcredist_x86.exe $(package)
	cp qt.conf $(package)
	cp 	$(WIN32QTPLUGS) $(package)/plugins/imageformats
	cp 	$(WIN32QTPLATFORMS) $(package)/plugins/platforms
	cp ../lib/GestureFollower/win32/GFLib.dll $(package)/$(winplug)
	cp ../lib/faust/win32/faust.dll $(package)/$(winplug)
	cp ../lib/faust/win32/llvm_math.ll $(package)/$(winplug)

linux:
	[ -d $(package) ] || mkdir -p $(package)
	make common
	make version=$(version) -f makedeb

