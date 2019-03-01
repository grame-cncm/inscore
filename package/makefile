
VERSION := $(shell cat ../version.txt)
system	:= $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))

MAKE ?= make
BUILDDIR    := ../build/bin

ifeq ($(system), MINGW)
  WIN32QTPATH ?= $(shell qmake --version | grep Using | sed -e 's/..*\([A-Za-z]:[^ ]*\)lib/\1/')
  QT5         ?= $(shell echo $(WIN32QTPATH) | sed -e 's/\/[5-9]\.[0-9]\/..*//')
  WIN32QT	  := QT5PRINTSUPPORT.DLL QT5WIDGETS.DLL QT5OPENGL.DLL QT5GUI.DLL QT5CORE.DLL QT5SVG.DLL QT5QML.DLL QT5WebSockets.DLL QT5Multimedia.DLL QT5MultimediaWidgets.DLL Qt5Network.dll Qt5Sensors.dll
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

package:= INScore-$(VERSION)
rsrc   := INScore-rsrc-$(VERSION)
viewer := INScoreViewer
docsrc := ../doc
docdst := ./doc

macapp  := $(viewer)-$(VERSION).app
winapp  := $(viewer)-$(VERSION).exe
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
	@echo "  make macos       # for Mac OS X"
	@echo "  make win64       # for Windows 64 bits"
	@echo "  make dist        # makes src package"
	@echo "  make doc         # makes doc"

dmg:
	hdiutil create $(package).dmg -fs HFS+ -srcfolder $(package) -format UDBZ -ov

cleanperms:
	@chmod -x  $(shell find $(package) -name "*.inscore")

macos:
	@[ -d $(package) ] || mkdir -p $(package)
	@$(MAKE) -C ../build link
	$(MAKE) common
	-[ -d $(package)/$(macapp) ] && rm -rf $(package)/$(macapp)
	cp -r $(BUILDDIR)/$(viewer).app $(package)/$(macapp)
	macdeployqt $(package)/$(macapp)
	$(MAKE) cleanperms
	cp -f ../src/guido2.ttf $(package)
	cd $(package) && ln -sf /Applications .
	@[ -d $(package)/IBundle ] || mkdir $(package)/IBundle
	cp $(ibundle)/IBundle $(package)/IBundle
	cp $(ibundle)/readme.txt $(package)/IBundle
	$(MAKE) dmg
		
common: 
	cp -r doc $(package)
	cp ReadMe.html $(package)
	cp ../src/changelog.txt $(package)
	cp -r ../interfaces $(package)
	$(MAKE) samples
		
doc:
	$(MAKE) -C $(docsrc)/webAPI html
	$(MAKE) copydoc
		
copydoc: 
	@[ -d $(docdst)/html ] || mkdir -p $(docdst)/html
	cp -f $(docsrc)/OSCMsg.pdf $(docdst)
	$(MAKE) -C $(docsrc) htmlclean
	rm -f $(docdst)/html/*
	rm -rf $(docdst)/WebAPI/*
	cp  $(docsrc)/OSCMsg/* $(docdst)/html
	cp  $(docsrc)/refcards/INScore-refcard-1.12.pdf $(docdst)
	cp  -r $(docsrc)/webAPI/build/html/ $(docdst)/WebAPI
	cd  $(docdst) && tar czf html.tgz html
	cd  $(docdst) && tar czf WebAPI.tgz WebAPI


samples:
	rm -rf $(package)/samples/*
	@[ -d $(package)/samples/Bundles ] || mkdir -p $(package)/samples/Bundles
	@echo ========================
	@echo " copying sample scripts"
	@echo ========================
	$(foreach s,$(scripts), cp -R ../scripts/$(s) $(package)/samples/;)
	@[ -d $(package)/samples ] || mkdir -p $(package)/samples
	cp ../scripts/mobile/*.ibundle $(package)/samples/Bundles;
	
dist :
	git archive --format=tar.gz --prefix=$(package)/ HEAD > $(package).tgz

win64:
	$(MAKE) wincommon
	cp -f $(bin64)/$(viewer).exe $(package)/$(viewer).exe
	cp -f $(bin64)/*.dll $(package)
	cp ../lib/libMusicXML/win64/libmusicxml2.dll $(package)/$(winplug)
	cp ../lib/GestureFollower/win64/GFLib64.dll $(package)/$(winplug)
	cp $(QT5)/vcredist/vcredist_msvc2013_x86.exe $(package)
	cp $(ibundle)/build/win64/release/IBundle.exe $(package)
	cp $(ibundle)/readme.txt $(package)/IBundle-ReadMe.txt
	cp rsrc/msvc*.dll $(package)/

wincommon:
	[ -d $(package) ] || mkdir -p $(package)
	[ -d $(package)/plugins/imageformats ] || mkdir -p $(package)/plugins/imageformats
	[ -d $(package)/plugins/platforms ] || mkdir -p $(package)/plugins/platforms
	$(MAKE) common
	cp qt.conf $(package)
	cp -f ../src/guido2.ttf $(package)
	cp  $(WIN32QT) $(package)
	cp 	$(WIN32QTPLUGS) $(package)/plugins/imageformats
	cp 	$(WIN32QTPLATFORMS) $(package)/plugins/platforms

