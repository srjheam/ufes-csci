#!/bin/bash

NC='\033[0m'
CYAN='\033[0;36m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
LIGHT_GREEN='\033[1;32m'

helpFunction()
{
   echo ""
   echo "Usage: $0 -e <test> -m"
   echo -e "\t-e Test directory name (e.g. dot_test)"
   echo -e "\t-m Run with valgrind, 1 for true, 0 for false"
   exit 1
}

VALGRIND=0

while getopts "e:m:" opt
do
   case "$opt" in
      e ) TEST="$OPTARG" ;;
      m ) VALGRIND="$OPTARG" ;;
      ? ) helpFunction ;;
   esac
done

# Print helpFunction in case parameters are empty
if [ -z "$TEST" ]
then
   helpFunction
fi

TEST_DIR="$TEST"
TARGET="$TEST_DIR/main"
INPUTS_DIR="$TEST_DIR/inputs"
OUTPUTS_DIR="$TEST_DIR/outputs"

echo ""
echo "${CYAN}${TEST}${NC}"
echo ""

make TEST=$TEST 1> /dev/null

for INPUT in ./$INPUTS_DIR/*
do
    NTEST="${INPUT##*/}"
    EXPECTED="$OUTPUTS_DIR/$NTEST"
    echo -n "#$NTEST"
    OUT=`$TARGET < $INPUT`
    DIFF=`echo "$OUT" | diff $EXPECTED -`
    if [ $VALGRIND -eq 1 ]
    then        
        (valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --verbose \
			 --log-file=$TEST/valgrind-out.txt \
			 --error-exitcode=1 \
			 $TARGET < $INPUT 1> /dev/null)

         VAL_OUT=$?
    fi

    if [ -z "${DIFF}" ] && [ $VAL_OUT -eq 0 ]
    then
        echo " ${LIGHT_GREEN}OK${NC}"
    else
        echo " ${RED}WA${NC}"

        echo "${YELLOW}Input${NC}"
        cat $INPUT
        echo ""

        echo "${YELLOW}Output${NC}"
        echo "$OUT"
        echo ""

        if [ -n "${DIFF}" ]
        then
            echo "${YELLOW}Expected${NC}"
            cat $EXPECTED
            echo ""

            echo "${YELLOW}Diff${NC}"
            echo $DIFF
            echo ""
        else
            echo "${YELLOW}Expected${NC}"
            echo ""

            echo "${YELLOW}Diff${NC}"
            echo ""
        fi

        if [ $VALGRIND -eq 1 ] && [ $VAL_OUT -ne 0 ]
        then
            echo "${YELLOW}Valgrind${NC}"
            echo "Leaks detected!"
            echo "Head to ${TEST_DIR}valgrind-out.txt"
            echo ""
        fi
        break
    fi
done
