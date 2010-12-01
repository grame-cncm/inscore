SRC = $(wildcard INScore/*.java)
CLASS = $(patsubst %.java, %.class, $(SRC) )
JNI   = $(patsubst INScore/%.java, jni/INScore_%.h, $(SRC) )

.PHONY: doc

class : $(CLASS)

jar : INScore.jar

INScore.jar : $(CLASS)
	jar cvf INScore.jar $(CLASS)

INScoreViewer : INScoreViewer.class
	java INScoreViewer 

clean :
	rm -f $(CLASS) *.class

doc:
	[ -d doc ] || mkdir doc
	javadoc -d doc INScore/*.java

##################################################################
# rule to make JNI headers
headers : $(JNI)

jni/INScore_%.h: INScore/%.class
	javah -jni -d jni $(patsubst INScore/%.class, INScore.%, $<) 

##################################################################
# rule for java compiling
%.class: %.java
	javac $< 

##################################################################
# platform specific utilities
win32 : INScore.dll jniINScore.dll

INScore.dll : ../cmake/release/INScore.dll
	cp ../cmake/release/INScore.dll .

jniINScore.dll : cmake/release/jniINScore.dll
	cp cmake/release/jniINScore.dll .

macos: libjniINScore.dylib

libjniINScore.dylib : cmake/Release/libjniINScore.dylib
	cp -f cmake/Release/libjniINScore.dylib .

linux: libjniINScore.so

libjniINScore.so : cmake/libjniINScore.so
	cp -f cmake/libjniINScore.so .

