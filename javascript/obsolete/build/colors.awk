
BEGIN {
	FS = "	";
	SEP = "";
	INDEX = 1;
	IOBJECT=0;
	
}

END {
}

################# papers generation
/^	"IObject"/ { 	
	if (IOBJECT==0)
		print "	edge [color=blue];";
	IOBJECT++
}
/^	"IObjectFactory"/ { 	
	if (IOBJECT)
		print "	edge [color=black];";
	IOBJECT = 0
}

/..*/ { 	
	print $0;
}
