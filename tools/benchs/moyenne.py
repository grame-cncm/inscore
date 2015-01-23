#!/usr/bin/python
#

import os
import sys
import string

n=0;
sum=0
first=True;	
for line in sys.stdin:
	if first == True:		# skip first line
		first = False
	else:
		sum += int(line)
		n += 1

if n > 0:
	print sum/n

