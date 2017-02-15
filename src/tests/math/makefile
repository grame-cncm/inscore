
OUT  = mathlex.cpp mathparse.cpp mathparse.hpp
YACC = bison
LEX = flex

code : $(OUT)

mathparse.cpp : math.y
mathparse.hpp : math.y
	$(YACC) -d -o mathparse.cpp   math.y

mathlex.cpp : math.l mathparse.hpp
	$(LEX)  -omathlex.cpp -I math.l

testparser: testparser.o mathparse.o mathlex.o 
	c++ testparser.o mathparse.o mathlex.o -o testparser

testparser.o : testparser.cpp mathparse.hpp
mathparse.o  : mathparse.cpp mathparse.hpp
mathlex.o  : mathlex.cpp mathparse.hpp

clean:
	rm -f $(OUT) *.o
