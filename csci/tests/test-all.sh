#!/bin/bash

helpFunction()
{
   echo ""
   echo "Usage: $0 -m"
   echo -e "\t-m Run with valgrind, 1 for true, 0 for false"
   exit 1
}

VALGRIND=0

while getopts "m:" opt
do
   case "$opt" in
      m ) VALGRIND="$OPTARG" ;;
      ? ) helpFunction ;;
   esac
done

for d in */ ; do
    d="${d%/}"
    sh run-test.sh -e $d -m $VALGRIND
done