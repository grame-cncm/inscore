
OUT  = ITLlex.cpp ITLparse.cpp ITLparse.hpp
YACC = bison
LEX = flex
PREFIX := ITL

code : $(OUT)

ITLparse.cpp : ITL.y
ITLparse.hpp : ITL.y
	$(YACC) -d -o ITLparse.cpp  -p $(PREFIX) ITL.y

ITLlex.cpp : ITL.l ITLparse.hpp 
	$(LEX)  -oITLlex.cpp -I -P$(PREFIX) ITL.l
	
doc :
	./makedoc

clean:
	rm -f $(OUT)
