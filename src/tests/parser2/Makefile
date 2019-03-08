
OUT  ?= parse2
FILE ?= tests

srcdir := ../../inscore2
subprojects :=  $(srcdir) $(srcdir)/eval $(srcdir)/parser src
sources = $(wildcard $(srcdir)/*/*.cpp $(srcdir)/[^i]*.cpp src/*.cpp) main.cpp
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
	@echo "    dot   : generates the tree with seq and par reduced, corresponding to $(FILE).inscore2"
	@echo "    parse : generates the parsed tree corresponding to $(FILE).inscore2 "
	@echo "    eval  : generates the evaluated tree corresponding to $(FILE).inscore2 "
	@echo "    paths : generates all the paths corresponding to the evaluation of $(FILE).inscore2 "

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

%.paths.dot: %.inscore2 $(OUT)
	$(OUT) -paths $< > $@	

%.eval.dot: %.inscore2 $(OUT)
	$(OUT) -eval $< > $@	

%.pdf: %.dot
	dot -Tpdf -o $@ $<



# DO NOT DELETE
