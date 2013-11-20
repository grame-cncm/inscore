#!/bin/sh

function wait () {
	what=$1
	count=0
	while [ $count -lt 100000 ]
	do
		[ -f $what ] && break
		count=$(($count + 1))
	done
}
