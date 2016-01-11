
OUT  = itlbundlelex.cpp itlbundleparse.cpp itlbundleparse.hpp
YACC = bison
LEX = flex

code : $(OUT)

itlbundleparse.cpp : itlbundle.y
itlbundleparse.hpp : itlbundle.y
	$(YACC) -d -o itlbundleparse.cpp  itlbundle.y

itlbundlelex.cpp : itlbundle.l itlbundleparse.hpp
	$(LEX)  -oitlbundlelex.cpp -I itlbundle.l
	
doc :
	./makedoc

clean:
	rm -f $(OUT)
