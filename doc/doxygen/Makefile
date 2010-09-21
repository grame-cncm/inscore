
# fetch the version number directly in the cmake conf file
VERSION = $(shell grep 'set .ITLFWKVERS' ../../cmake/CMakeLists.txt | sed -e 's/[^0-9.]//g')
SP = IASL-$(VERSION)
	
doc:
	doxygen
	cd latex && make
	mv latex/refman.pdf $(SP).pdf
	-[ -d  $(SP) ] && rm -rf $(SP)
	mkdir $(DEST)$(SP)
	cp $(SP).pdf $(DEST)$(SP)
	cp -R html $(DEST)$(SP)

clean:
	rm -rf html latex $(SP).pdf $(SP).tgz $(SP)
