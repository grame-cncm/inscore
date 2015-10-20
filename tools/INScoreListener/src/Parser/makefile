
OUT  = filterlex.cpp filterparse.cpp filterparse.hpp
YACC = bison
LEX = flex

code : $(OUT)

filterparse.cpp : filter.y
filterparse.hpp : filter.y
	$(YACC) -d -o filterparse.cpp  filter.y

filterlex.cpp : filter.l filterparse.hpp
	$(LEX)  -ofilterlex.cpp -I filter.l
	
doc :
	./makedoc

clean:
	rm -f $(OUT)
