
BEGIN {
	start=0;
}

# a flag to isolate the grammar section
/%%/ {
	start = start + 1
}


# keep the definitions and the comments
/^[a-zA-Z\/]/ {
	if (start == 1) 
		print $0
}

# keep the definitions continuation and end
/^[ 	]+[|;]+/ { 	
	if (start == 1) 
		print $0
}
