version := 1.18
system	:= $(shell uname -s)
ifeq ($(system), MINGW32_NT-6.1) 
	win32 = yes
else
ifeq ($(system), MINGW32_NT-6.2) 
	win32 = yes
else
ifeq ($(system), CYGWIN_NT-6.1) 
	win32 = yes
endif
endif
endif

ifeq ($(system), Darwin)
  BUILD    := ../build/macos/Release
else
ifdef win32 
  WIN32QTPATH ?= $(shell qmake --version | grep Using | sed -e 's/..*\([A-Za-z]:[^ ]*\)lib/\1/')
  QT5         ?= $(shell echo $(WIN32QTPATH) | sed -e 's/\/[5-9]\.[0-9]\/..*//')
  WIN32QT	  := QT5PRINTSUPPORT.DLL QT5WIDGETS.DLL QT5OPENGL.DLL QT5GUI.DLL QT5CORE.DLL QT5SVG.DLL QT5QML.DLL QT5WebSockets.DLL QT5Multimedia.DLL QT5MultimediaWidgets.DLL Qt5Network.dll
  ifeq ($(QT5), /c/Qt/Qt5.4.0)
   WIN32QT	  := $(WIN32QT) ICUIN53.DLL ICUUC53.DLL ICUDT53.DLL
  endif
  WIN32QT	  := $(patsubst %, $(WIN32QTPATH)/bin/%, $(WIN32QT))
  WIN32QTPLUGS     := qgif.dll qtiff.dll qjpeg.dll
  WIN32QTPLATFORMS := qminimal.dll qoffscreen.dll qwindows.dll
  WIN32QTPLUGS     := $(patsubst %, $(WIN32QTPATH)/plugins/imageformats/%, $(WIN32QTPLUGS))
  WIN32QTPLATFORMS := $(patsubst %, $(WIN32QTPATH)/plugins/platforms/%, $(WIN32QTPLATFORMS))
  bin    := ../build/win32/release
  bin64   := ../build/win64/release
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
ibundle := ../tools/IBundle

#########################
# scripts provided as samples are now stored in a file
scripts := $(shell cat samples-list.txt)

#########################
.PHONY: doc rsrc

help:
	@echo This makefile builds the INScore package.
	@echo usage:
	@echo "  make macosx      # for Mac OS X"
	@echo "  make win32       # for Windows 32 bits"
	@echo "  make win64       # for Windows 64 bits"
	@echo "  make linux       # for Linux (only build the rsrc)"
	@echo "  make src         # makes src package"
	@echo "  make rsrc        # makes rsrc for SF FRS"
	@echo "  make doc         # makes doc"
	@echo "  make interfaces  # makes the list, csound and python packages"

dmg:
	hdiutil create $(package).dmg -srcfolder $(package) -ov

cleanperms:
	@chmod -x  $(shell find $(package) -name "*.inscore")

IFWK=Frameworks/INScore.framework/Versions/Current/INScore
macosx:
	@[ -d $(package) ] || mkdir -p $(package)
	[ -h ../build/macos/lib ] || make -C ../build link
	make common
	-[ -d $(package)/$(macapp) ] && rm -rf $(package)/$(macapp)
	cp -r $(BUILD)/$(viewer).app $(package)/$(macapp)
	macdeployqt $(package)/$(macapp)
	@cd  $(package)/$(macapp)/Contents && ../../../localise INScore MacOS/INScoreViewer @rpath
	@cd  $(package)/$(macapp)/Contents && ../../../localise GUIDOEngine $(IFWK) @executable_path/../Frameworks
	@cd  $(package)/$(macapp)/Contents && ../../../localise guidoar $(IFWK) @executable_path/../Frameworks
	make cleanperms
	cp -f ../src/guido2.ttf $(package)
	cd $(package) && ln -sf /Applications .
	@[ -d $(package)/IBundle ] || mkdir $(package)/IBundle
	cp $(ibundle)/IBundle $(package)/IBundle
	cp $(ibundle)/readme.txt $(package)/IBundle
	make dmg
		
common: 
	cp -r doc $(package)
	cp readme.txt $(package)
	cp ../src/changelog.txt $(package)
	make samples
		
doc:
	make -C $(docsrc)/webAPI html
	make copydoc
		
copydoc: 
	@[ -d $(docdst)/html ] || mkdir -p $(docdst)/html
	cp -f $(docsrc)/OSCMsg.pdf $(docdst)
	make -C $(docsrc) htmlclean
	rm -f $(docdst)/html/*
	rm -rf $(docdst)/WebAPI/*
	cp  $(docsrc)/OSCMsg/* $(docdst)/html
	cp  $(docsrc)/refcards/INScore-refcard-1.12.pdf $(docdst)
	cp  -r $(docsrc)/webAPI/build/html/ $(docdst)/WebAPI
	cd  $(docdst) && tar czf html.tgz html
	cd  $(docdst) && tar czf WebAPI.tgz WebAPI

interfaces:
	@[ -d $(rsrc)/$(interf) ] || mkdir -p $(rsrc)/$(interf)
	tar czf $(rsrc)/$(interf)/python.tgz ../$(interf)/python
	tar czf $(rsrc)/$(interf)/lisp.tgz ../$(interf)/lisp
	tar czf $(rsrc)/$(interf)/csound.tgz ../$(interf)/csound	

scripts:
	@[ -d $(rsrc)/scripts/bundles ] || mkdir -p $(rsrc)/scripts/bundles
	cp -R ../scripts/Standalone/* $(rsrc)/scripts
	cp -R ../scripts/mobile/*.ibundle $(rsrc)/scripts/bundles
	rm -f $(shell find $(rsrc)/scripts -name "*DS_Store")
	cd $(rsrc) && tar czf scripts.tgz scripts

patches:
	@[ -d $(rsrc)/patches ] || mkdir -p $(rsrc)/patches
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
	rm -rf $(package)/samples/*
	@[ -d $(package)/samples/Bundles ] || mkdir -p $(package)/samples/Bundles
	@echo ========================
	@echo " copying sample scripts"
	@echo ========================
	$(foreach s,$(scripts), cp -R ../scripts/$(s) $(package)/samples/;)
	@[ -d $(package)/samples ] || mkdir -p $(package)/samples
	cp ../scripts/mobile/*.ibundle $(package)/samples/Bundles;
	
src:
	@[ -d $(package)-src ] || mkdir -p $(package)-src
	@[ -d $(package)-src/build ] || mkdir -p $(package)-src/build
	@[ -d $(package)-src/rsrc/images ] || mkdir -p $(package)-src/rsrc/images
	@[ -d $(package)-src/scripts ] || mkdir -p $(package)-src/scripts
	cp -rf ../src $(package)-src/
	cp -rf ../build/*.pro $(package)-src/build
	cp -rf ../build/Makefile $(package)-src/build
	cp -rf ../build/Info.plist $(package)-src/build
	cp -rf ../build/qt-arch $(package)-src/build
	cp -rf ../build/vs-* $(package)-src/build
	cp -rf ../rsrc/*.qrc $(package)-src/rsrc
	cp -rf ../rsrc/INScoreViewer.* $(package)-src/rsrc
	cp -rf ../rsrc/images/*.png $(package)-src/rsrc/images
	cp -rf ../rsrc/grame.png $(package)-src/rsrc/
	cp -rf ../rsrc/mobile $(package)-src/rsrc/
	cp -rf ../rsrc/fonts $(package)-src/rsrc/
	cp -rf ../rsrc/android $(package)-src/rsrc/
	cp -rf ../lib $(package)-src/
	cp -rf ../win32 $(package)-src/
	cp -rf ../tools $(package)-src/
	cp -rf ../scripts/mobile $(package)-src/scripts/
	cp readme.txt $(package)-src
	cp ../readme.txt $(package)-src/install
	cp -r doc $(package)-src
	make srcclean
	@echo ===================================	
	@echo manually cleanup src folder from hidden, unused and unwanted files
	@echo ===================================	
	tar czf $(package)-src.tgz $(package)-src

FMWK := $(shell find $(package)-src/lib -name "*.framework")
srcclean:
	rm -rf $(package)-src/lib/poppler
	rm -rf $(package)-src/lib/lua
	rm -rf $(package)-src/lib/javascript
	rm -rf $(package)-src/lib/Guido*/lib
	rm -rf $(package)-src/tools/QtOSC*
	rm -rf $(package)-src/tools/benchs
	cd $(package)-src/tools && rm -f E* *.awk getMethods Makefile IBundle/IBundle*
	cd $(package)-src/tools/inscore2inscore100 && rm -rf inscore2inscore100 cmake/Debug cmake/Release
	cd $(package)-src/tools/inscore2inscore90 && rm -rf inscore2inscore90 cmake/Debug cmake/Release
	cd $(package)-src/tools/INScoreListener/build && rm -rf Debug Release *.build *.xcodeproj
	cd $(package)-src/scripts/mobile && rm -rf *.ibundle *.graffle
	rm -rf $(package)-src/tools/IBundle/build/macos
	rm -rf $(FMWK)

win32:
	make wincommon
	cp -f $(bin)/$(viewer).exe $(package)/$(viewer).exe
	cp -f $(bin)/*.dll $(package)
	cp $(QT5)/vcredist/vcredist_x86.exe $(package)
	cp ../lib/libMusicXML/win32/libmusicxml2.dll $(package)/$(winplug)
	cp ../lib/GestureFollower/win32/GFLib.dll $(package)/$(winplug)
	cp ../lib/faust/win32/faust.dll $(package)/$(winplug)
	cp ../lib/faust/win32/llvm_math.ll $(package)/$(winplug)
	cp $(ibundle)/build/win32/release/IBundle.exe $(package)
	cp $(ibundle)/readme.txt $(package)/IBundle-ReadMe.txt

win64:
	make wincommon
	cp -f $(bin64)/$(viewer).exe $(package)/$(viewer).exe
	cp -f $(bin64)/*.dll $(package)
	cp ../lib/libMusicXML/win64/libmusicxml2.dll $(package)/$(winplug)
	cp ../lib/GestureFollower/win64/GFLib64.dll $(package)/$(winplug)
	cp $(QT5)/vcredist/vcredist_msvc2013_x86.exe $(package)
	cp $(ibundle)/build/win64/release/IBundle.exe $(package)
	cp $(ibundle)/readme.txt $(package)/IBundle-ReadMe.txt

wincommon:
	[ -d $(package) ] || mkdir -p $(package)
	[ -d $(package)/plugins/imageformats ] || mkdir -p $(package)/plugins/imageformats
	[ -d $(package)/plugins/platforms ] || mkdir -p $(package)/plugins/platforms
	make common
	cp qt.conf $(package)
	cp -f ../src/guido2.ttf $(package)
	cp  $(WIN32QT) $(package)
	cp 	$(WIN32QTPLUGS) $(package)/plugins/imageformats
	cp 	$(WIN32QTPLATFORMS) $(package)/plugins/platforms

linux:
	[ -d $(package) ] || mkdir -p $(package)
	make common
	make version=$(version) -f makedeb

