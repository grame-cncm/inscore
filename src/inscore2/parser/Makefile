
YACC = bison
LEX = flex
PREFIX := INSCOREV2

BASE := inscorev2

parser: inscoreparse.cpp inscorelex.cpp

inscoreparse.cpp : $(BASE).y
inscoreparse.hpp : $(BASE).y
	$(YACC) -d -o inscoreparse.cpp  -p $(PREFIX) $(BASE).y

inscorelex.cpp : $(BASE).l inscoreparse.hpp 
	$(LEX)  --header-file=inscorelex.hpp -oinscorelex.cpp -I -P$(PREFIX) $(BASE).l

tokens:
	grep return $(BASE).l | sed -e 's/^..*return \([A-Z][A-Z0-9]*\)..*/%token \1/' | sort -u

clean:
	rm -f $(OUT) $(OBJ) inscorelex.hpp


# DO NOT DELETE

