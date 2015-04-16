# Create incore script from flt file.

BEGIN { 
	FS = ":";
	accepted = "";
	rejected = "";
}

/^accept:/ {
	accepted = accepted " " "\"" $2 "\"";
}


/^reject:/ {
	rejected = rejected " " "\"" $2 "\"";
}
END {
	if(accepted != "")
		print "/ITL/filter accept" accepted ";";
	if(rejected != "")
		print "/ITL/filter reject" rejected ";";
 }
