
#OUT  = yylex.cxx yyparse.cxx yyparse.hxx
OUT  = mapping.tab.cpp mapping.tab.hpp lex.libmap.cpp
YACC = bison
LEX = flex
PREFIX := libmap

code : $(OUT)

mapping.tab.cpp : mapping.y
	$(YACC) -d -o mapping.tab.cpp -p $(PREFIX) mapping.y

mapping.tab.hpp : mapping.y
	$(YACC) -d  -o mapping.tab.cpp -p $(PREFIX) mapping.y

lex.libmap.cpp : mapping.l mapping.tab.hpp
	$(LEX) -I -olex.libmap.cpp -P$(PREFIX) mapping.l

yyparse.cpp : mapping.y
	$(YACC) -d --debug -o yyparse.cxx  -p $(PREFIX) mapping.y

yyparse.hxx : mapping.y
	$(YACC) --debug -d -o yyparse.cxx  -p $(PREFIX) mapping.y

yylex.cxx : mapping.l yyparse.hxx
	$(LEX)  -oyylex.cxx -I -P$(PREFIX) mapping.l

clean:
	rm -f $(OUT)
