
OUT  = ../jsonlex.cpp ../jsonparse.cpp ../jsonparse.hpp
YACC = bison
LEX = flex
PREFIX := json

code : $(OUT)

../jsonparse.cpp : json.y
	$(YACC) -d -o jsonparse.cpp  -p $(PREFIX) json.y
	mv -f jsonparse.cpp ..
	mv -f jsonparse.hpp ..

../jsonparse.hpp : ../jsonparse.cpp

#../jsonparse.hpp : json.y
#	$(YACC) -d -o jsonparse.cpp  -p $(PREFIX) json.y
#	cp jsonparse.hpp ..

../jsonlex.cpp : json.l jsonparse.hpp
	$(LEX)  -ojsonlex.cpp -I -P$(PREFIX) json.l
	mv -f jsonlex.cpp ..
	
clean:
	rm -f $(OUT)
