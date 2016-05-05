#
# 
#

all : 
	make checklink
	tsc 

checklink :
	[ -d src ] || ln -s ../src .

check :
	make  -C ../build check
