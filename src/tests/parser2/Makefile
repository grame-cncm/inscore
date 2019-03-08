
OUT ?= parse2

srcdir := ../../inscore2
subprojects :=  $(srcdir) $(srcdir)/eval $(srcdir)/parser src
sources = $(wildcard $(srcdir)/*/*.cpp $(srcdir)/[^i]*.cpp src/*.cpp) main.cpp
objects = $(patsubst src%, obj/src%, $(patsubst ../../inscore2%,obj%, $(sources:%.cpp=%.o)))

CXXFLAGS += $(addprefix -I, $(subprojects)) -DTESTV2


##############################################################
# the targets
##############################################################
all : $(OUT)

test:
	@echo $(sources)
	@echo
	@echo $(objects)

parser:
	make -C $(srcdir)/parser

$(OUT): $(objects)
	$(CXX) $(objects) -o $(OUT)

clean:
	rm -f $(OUT) $(objects)

dot:
	./parse2 $(A) $(B) > test.dot
	dot -Tpdf -o test.pdf test.dot
	open test.pdf

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


# DO NOT DELETE
