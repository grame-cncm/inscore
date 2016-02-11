
/^\/ITL\/scene\/rect\/circle\/score / {
# accept
print $0;
addLine = 1;
}

/^\/ITL\/scene\/line2 / {
# accept
print $0;
addLine = 1;
}

/^.* scale .*/ {
# accept
print $0;
addLine = 1;
}


/^\/ITL\/scene\/rect\/circle / {
# reject
filterLine = 1;
}

/^\/ITL\/scene\/line.* / {
# reject
filterLine = 1;
}

/^.* load .*/ {
# reject
filterLine = 1;
}

/^.* rootPath .*/ {
# reject
filterLine = 1;
}

/.*/ {
if(filterLine == 0 && addLine == 0 && $0 != "") {
	print $0;
}
filterLine = 0;
addLine = 0;
}
