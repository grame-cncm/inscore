
OUT  = IExprlex.cpp IExprParse.cpp IExprParse.hpp
YACC = bison
LEX = flex
PREFIX := IExpr

code : $(OUT)

IExprParse.cpp : IExpr.y
IExprParse.hpp : IExpr.y
	$(YACC) -d -o IExprParse.cpp  -p $(PREFIX) IExpr.y

IExprlex.cpp : IExpr.l IExprParse.hpp
	$(LEX)  -oIExprlex.cpp -I -P$(PREFIX) IExpr.l

clean:
	rm -f $(OUT)
