
VERSION := $(shell cat ../version.txt)
system	:= $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), Darwin)
	TARGET  = macos
endif
ifeq ($(system), MINGW)
	TARGET = windows
endif
ifeq ($(system), Linux)
	TARGET = linux
endif


MAKE ?= make
BUILD    := build
BUILDDIR := ../build/bin

package:= INScore-$(VERSION)
docsrc := ../doc
docdst := ./doc


#########################
.PHONY: doc rsrc macos linux windows

package: $(TARGET)

help:
	@echo This makefile builds the INScore package.
	@echo Available targets are:
	@echo "   macos     for Mac OS X"
	@echo "   linux     for linux systems"
	@echo "   dist      make the src package"
	@echo "   doc       regenerate the documentation"
	@echo "Option:"
	@echo "   PREFIX    the destination prefix (used on linux only)"

macos:
	@[ -d $(BUILD) ] || mkdir -p $(BUILD)
	macdeployqt $(BUILDDIR)/INScoreViewer.app
	cd $(BUILD) && cmake ..
	cmake --build $(BUILD) --config Release --target install
	cd $(BUILD)/$(package) && ln -s -f /Applications . 
	hdiutil create $(package).dmg -fs HFS+ -srcfolder $(BUILD)/$(package) -format UDBZ -ov

linux:
	@[ -d $(BUILD) ] || mkdir -p $(BUILD)
	cd $(BUILD) && cmake -DCMAKE_INSTALL_PREFIX=$(PREFIX) ..
	cmake --build $(BUILD) --config Release --target install
		
doc:
	$(MAKE) -C $(docsrc)/webAPI html
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
	
dist :
	git archive --format=tar.gz --prefix=$(package)/ HEAD > $(package).tgz
	
windows :
	echo "Use the MakePkg.bat script to generate the inscore installer"
