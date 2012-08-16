
CXXFLAGS := -I../../misc -I../../segments -I../../relations -I..
OBJ := testparser.o ../../misc/lmrational.o mapping.tab.o lex.libmap.o

testparser: $(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -lm -o testparser 

clean:
	rm -f $(OBJ)
	make -C .. clean

testparser.o: ../../segments/TInterval.h ../../segments/TSegment.h ../../segments/TSegmentation.h ../../segments/TVariety.h
testparser.o: ../../segments/TRefinement.h ../../misc/lmtools.h ../../relations/TComposition.h ../../relations/TMapping.h
testparser.o: ../../relations/TRefinedComposition.h ../../relations/TRelation.h ../../relations/TRefinedRelation.h 
testparser.o: ../mapping.tab.cpp ../mapping.tab.hpp ../lex.libmap.cpp 

mapping.tab.o: ../mapping.tab.cpp 
	g++ $(CXXFLAGS) ../mapping.tab.cpp -c 

lex.libmap.o: ../lex.libmap.cpp 
	g++ $(CXXFLAGS) ../lex.libmap.cpp -c

../lex.libmap.cpp : ../mapping.l
	make -C ..
../mapping.tab.cpp : ../mapping.y
	make -C ..

../yylex.cxx : ../mapping.l
	make -C ..
../yyparse.cxx : ../mapping.y
	make -C ..
../yyparse.hxx : ../mapping.y
	make -C ..

../misc/lmrational.o : ../misc/lmrational.h
