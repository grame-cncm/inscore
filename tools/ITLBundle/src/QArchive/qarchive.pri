QARCHIVE = $$PWD

SOURCES +=  $$QARCHIVE/QArchive.cpp \
	    $$QARCHIVE/QSubIODevice.cpp \
	    $$QARCHIVE/QArchiveHeader.cpp
            
HEADERS +=  $$QARCHIVE/QArchive.h \
	    $$QARCHIVE/QSubIODevice.h \
	    $$QARCHIVE/QArchiveHeader.h \
	    $$QARCHIVE/Tree.h \
	    $$QARCHIVE/Tree.tpp
            
INCLUDEPATH +=  $$PWD \
		$$QARCHIVE/../../../../src/libmapping/src/misc/
