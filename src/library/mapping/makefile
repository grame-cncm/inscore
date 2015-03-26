
OUT  = maplex.c++ mapparse.c++ mapparse.h++
YACC = bison
LEX = flex
PREFIX := itlmap

code : $(OUT)

mapparse.c++ : mapping.y
	$(YACC) -d -o mapparse.c++  -p $(PREFIX) mapping.y

mapparse.h++ : mapping.y
	$(YACC) -d -o mapparse.c++  -p $(PREFIX) mapping.y

maplex.c++ : mapping.l mapparse.h++
	$(LEX)  -omaplex.c++ -I -P$(PREFIX) mapping.l

clean:
	rm -f $(OUT)
