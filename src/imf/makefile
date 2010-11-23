
APPL = xml
OUT  = xmllex.c++ xmlparse.cpp xmlparse.hpp
OBJ  = xmlparse.o
CXXFLAGS = -I.. -DMAIN
YACC = bison
LEX = flex
PREFIX := imf

code : $(OUT)

xml : $(OUT)
	g++ $(CXXFLAGS) xmlparse.cpp -lstdc++ -o $(APPL)

xmlparse.cpp : xml.y
	$(YACC) -d -o xmlparse.cpp  -p $(PREFIX) xml.y

xmlparse.h++ : xml.y
	$(YACC) -d -o xmlparse.cpp  -p $(PREFIX) xml.y

xmllex.c++ : xml.l xmlparse.h++
	$(LEX)  -oxmllex.c++ -I -P$(PREFIX) xml.l

clean:
	rm -f $(APPL) $(OUT) $(OBJ)
