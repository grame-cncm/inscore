# Create awk filter script from flt file.

# format a item with escape character
function formatItem(item) {
	if (substr(item, 0, 1) == "/") {
		# OSC address
		gsub("\*", ".*", $2);
		gsub("\/", "\\\/", $2);
		$2 = $2 " ";
	} else {
		$2 = ".*" " " $2 " " ".*"
	}
}

BEGIN { 
	FS = ":";
	accepted = "";
	rejected = "";
}

/^accept:/ {
	formatItem($2);
	# Add new awk rule for the item
	accepted = accepted "\n" "/^" $2 "/ {\n";
	accepted = accepted "# accept\n";
	accepted = accepted "print $0;\n";
	accepted = accepted "addLine = 1;\n";
	accepted = accepted "}\n";
}


/^reject:/ {
	formatItem($2);
	# Add new awk rule for the item
	rejected = rejected "\n" "/^" $2 "/ {\n";
	rejected = rejected "# reject\n";
	rejected = rejected "filterLine = 1;\n";
	rejected = rejected "}\n";
}
END {
	# print all rules
	if(accepted != "")
		print accepted;
	if(rejected != "")
		print rejected;

	# print a common rule for all lines
	print "\/.*\/ {";
	print "if(filterLine == 0 && addLine == 0 && $0 != \"\") {";
	print "	print $0;";
	print "}";
	print "filterLine = 0;";
	print "addLine = 0;";
	print "}";
}
