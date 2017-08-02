#!/bin/bash

# Takes all files listed in files_to_link, which are assumed to
# exist in ../../misc/eval, and creates a symbolic link to them
#
# The option --clean removes the created links
# 
# A flag file .links_created hinders that the links are created
# if the script was already called.  This is useful for the make
# file which calls this script every time.

if [ -e ./files_to_link ]
then
    list=`cat ./files_to_link`
    if [ "$1" == "--clean" ]; then
	for i in $list; do rm $i ; done
	rm .links_created
    else
	if [ ! -e .links_created ] ; then
	    for i in $list; do ln -fs ../../misc/eval/$i . ; done
	    touch .links_created
	fi
    fi
fi
