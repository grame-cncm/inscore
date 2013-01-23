BEGIN { 
	pm = "-"
	gs = "-"
	autre = 0
	prefix = "extern const char* k"
	suffix = "Method"
	sep = "_"
} 

{ 
	if ($1 == pm) 
		print prefix $1 sep gs $3 suffix ";"
	else if ( autre > 0)
		print prefix pm sep gs suffix ";"
	if (pm == $1)
		autre = 0
	else 
		autre = 1
	pm = $1
	gs = $3
}