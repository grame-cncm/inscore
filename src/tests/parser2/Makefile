
OUT  ?= parse2
FILE ?= tests

srcdir := ../../inscore2
subprojects :=  $(srcdir) $(srcdir)/eval $(srcdir)/parser src
sources = $(wildcard $(srcdir)/[^s]*/*.cpp $(srcdir)/[^i]*.cpp src/*.cpp) main.cpp
objects = $(patsubst src%, obj/src%, $(patsubst ../../inscore2%,obj%, $(sources:%.cpp=%.o)))

CXXFLAGS += $(addprefix -I, $(subprojects)) -DTESTV2

all : $(OUT)

##############################################################
help:
	@echo "Build and run $(OUT) with various output"
	@echo "Available targets are:"
	@echo "    all (default)  : build $(OUT) tool"
	@echo "    parser : re-build the parser"
	@echo "    clean  : remove $(OUT) and object files"
	@echo 
	@echo "Targets to run $(OUT) with various output:"
	@echo "    dot    : generates the tree with seq and par reduced, corresponding to $(FILE).inscore2"
	@echo "    parse  : generates the parsed tree corresponding to $(FILE).inscore2 "
	@echo "    eval   : generates the evaluated tree corresponding to $(FILE).inscore2 "
	@echo "    paths  : generates all the paths corresponding to the evaluation of $(FILE).inscore2 without delay report"
	@echo "    pathd  : generates all the paths corresponding to the evaluation of $(FILE).inscore2 with delay report"

##############################################################
# the targets
##############################################################
test:
	@echo $(sources)
	@echo
	@echo $(objects)

parser:
	make -C $(srcdir)/parser

$(OUT): $(objects)
	$(CXX) $(objects) -o $(OUT)

clean:
	rm -f $(OUT) $(objects) $(FILE).*.pdf

dot: $(FILE).pdf $(OUT)
	open $(FILE).pdf

parse: $(FILE).parse.pdf $(OUT)
	open $(FILE).parse.pdf

eval: $(FILE).eval.pdf $(OUT)
	open $(FILE).eval.pdf

paths: $(FILE).paths.pdf $(OUT)
	open $(FILE).paths.pdf

pathd: $(FILE).pathd.pdf $(OUT)
	open $(FILE).pathd.pdf

depends:
	makedepend $(CXXFLAGS) $(sources)

##############################################################
# rules for building to obj folder
##############################################################
obj/%.o: $(srcdir)/%.cpp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS)  -std=c++11 $< -o $@

obj/src/%.o: src/%.cpp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS)  -std=c++11 $< -o $@

%.o: %.cpp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS)  -std=c++11 $< -o $@

##############################################################
# rules to generate the various output
##############################################################
%.dot: %.inscore2 $(OUT)
	$(OUT) $(OPTION) $< > $@	

%.parse.dot: %.inscore2 $(OUT)
	$(OUT) -parse $< > $@	

%.apply.dot: %.inscore2 $(OUT)
	$(OUT) -apply $< > $@	

%.pathd.dot: %.inscore2 $(OUT)
	$(OUT) -paths $< > $@	

%.paths.dot: %.inscore2 $(OUT)
	$(OUT) -pathsonly $< > $@	

%.eval.dot: %.inscore2 $(OUT)
	$(OUT) -eval $< > $@	

%.pdf: %.dot
	dot -Tpdf -o $@ $<



# DO NOT DELETE

../../inscore2/eval/addressEval.o: ../../inscore2/eval/addressEval.h
../../inscore2/eval/addressEval.o: ../../inscore2/INode.h
../../inscore2/eval/addressEval.o: ../../inscore2/TEnv2.h
../../inscore2/eval/addressEval.o: ../../inscore2/eval/expandEval.h
../../inscore2/eval/evaluator2.o: ../../inscore2/eval/evaluator2.h
../../inscore2/eval/evaluator2.o: ../../inscore2/INode.h
../../inscore2/eval/evaluator2.o: ../../inscore2/TEnv2.h
../../inscore2/eval/evaluator2.o: ../../inscore2/eval/expandEval.h
../../inscore2/eval/evaluator2.o: ../../inscore2/eval/parseEval.h
../../inscore2/eval/evaluator2.o: ../../inscore2/TreeTools.h
../../inscore2/eval/expandEval.o: ../../inscore2/eval/expandEval.h
../../inscore2/eval/expandEval.o: ../../inscore2/INode.h
../../inscore2/eval/expandEval.o: ../../inscore2/TEnv2.h
../../inscore2/eval/expandEval.o: ../../inscore2/TreeTools.h
../../inscore2/eval/jsEval.o: ../../inscore2/eval/jsEval.h
../../inscore2/eval/jsEval.o: ../../inscore2/INode.h ../../inscore2/TEnv2.h
../../inscore2/eval/jsEval.o: ../../inscore2/parser/IParser2.h
../../inscore2/eval/parseEval.o: ../../inscore2/eval/parseEval.h
../../inscore2/eval/parseEval.o: ../../inscore2/INode.h
../../inscore2/eval/parseEval.o: ../../inscore2/TEnv2.h
../../inscore2/eval/parseEval.o: ../../inscore2/eval/expandEval.h
../../inscore2/parser/IParser2.o: ../../inscore2/parser/IParser2.h
../../inscore2/parser/IParser2.o: ../../inscore2/INode.h
../../inscore2/parser/IParser2.o: ../../inscore2/TEnv2.h
../../inscore2/parser/IParser2.o: ../../inscore2/eval/parseEval.h
../../inscore2/parser/IParser2.o: ../../inscore2/eval/addressEval.h
../../inscore2/parser/inscorelex.o: ../../inscore2/parser/IParser2.h
../../inscore2/parser/inscorelex.o: ../../inscore2/INode.h
../../inscore2/parser/inscorelex.o: ../../inscore2/TEnv2.h
../../inscore2/parser/inscorelex.o: ../../inscore2/parser/inscoreparse.hpp
../../inscore2/parser/inscoreparse.o: ../../inscore2/parser/IParser2.h
../../inscore2/parser/inscoreparse.o: ../../inscore2/INode.h
../../inscore2/parser/inscoreparse.o: ../../inscore2/TEnv2.h
../../inscore2/parser/inscoreparse.o: ../../inscore2/parser/inscoreparse.hpp
../../inscore2/parser/inscoreparse.o: ../../inscore2/parser/inscorelex.hpp
../../inscore2/INode.o: ../../inscore2/INode.h ../../inscore2/TEnv2.h
../../inscore2/INode.o: ../../inscore2/TreeTools.h
../../inscore2/TEnv2.o: ../../inscore2/INode.h ../../inscore2/TEnv2.h
../../inscore2/TreeTools.o: ../../inscore2/TreeTools.h
../../inscore2/pathsList.o: ../../inscore2/pathsList.h ../../inscore2/INode.h
../../inscore2/pathsList.o: ../../inscore2/TEnv2.h
../../inscore2/reduce.o: ../../inscore2/reduce.h ../../inscore2/INode.h
../../inscore2/reduce.o: ../../inscore2/TEnv2.h ../../inscore2/pathsList.h
src/dotprinter.o: src/dotprinter.h ../../inscore2/INode.h
src/dotprinter.o: ../../inscore2/TEnv2.h
src/inscorev1printer.o: src/inscorev1printer.h ../../inscore2/INode.h
src/inscorev1printer.o: ../../inscore2/TEnv2.h ../../inscore2/pathsList.h
src/oscprinter.o: src/oscprinter.h ../../inscore2/INode.h
src/oscprinter.o: ../../inscore2/TEnv2.h
main.o: ../../inscore2/parser/IParser2.h ../../inscore2/INode.h
main.o: ../../inscore2/TEnv2.h ../../inscore2/reduce.h src/dotprinter.h
main.o: src/oscprinter.h src/inscorev1printer.h
main.o: ../../inscore2/eval/parseEval.h ../../inscore2/eval/evaluator2.h
main.o: ../../inscore2/pathsList.h
