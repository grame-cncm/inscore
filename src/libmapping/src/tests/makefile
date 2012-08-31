
CXXFLAGS := -I../misc -I../segments -I../relations
OBJ := Tests.o ../misc/rational.o

testlib: $(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -lm -o testlib 

clean:
	rm -f $(OBJ)

Tests.o: ../segments/TInterval.h ../segments/TSegment.h ../segments/TSegmentation.h ../segments/TVariety.h
Tests.o: ../segments/TRefinement.h ../misc/lmtools.h ../relations/TComposition.h ../relations/TMapping.h
Tests.o: ../relations/TRefinedComposition.h ../relations/TRelation.h ../relations/TRefinedRelation.h
../misc/rational.o : ../misc/rational.h