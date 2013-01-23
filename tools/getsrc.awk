BEGIN { 
	pm = "-"
	gs = "-"
	autre = 0
	prefix = "const char* k"
	suffix = "Method	= \""
	sep = "_"
} 

{ 
	if ($1 == pm) 
		print prefix $1 sep gs $3 suffix $1 "\";		// " gs, $3
	else if ( autre > 0)
		print prefix pm sep gs suffix pm "\";		// " gs
	if (pm == $1)
		autre = 0
	else 
		autre = 1
	pm = $1
	gs = $3
}