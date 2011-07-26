
OUT  = ITLlex.c++ ITLparse.c++ ITLparse.h++
YACC = bison
LEX = flex
PREFIX := ITL

code : $(OUT)

ITLparse.c++ : ITL.y
	$(YACC) -d -o ITLparse.c++  -p $(PREFIX) ITL.y

ITLparse.h++ : ITL.y
	$(YACC) -d -o ITLparse.c++  -p $(PREFIX) ITL.y

ITLlex.c++ : ITL.l ITLparse.h++
	$(LEX)  -oITLlex.c++ -I -P$(PREFIX) ITL.l

clean:
	rm -f $(OUT)
