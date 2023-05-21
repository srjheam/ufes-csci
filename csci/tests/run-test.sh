#!/bin/bash
set -e

NC='\033[0m'
CYAN='\033[0;36m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
LIGHT_GREEN='\033[1;32m'

helpFunction()
{
   echo ""
   echo "Usage: $0 -e <test>"
   echo -e "\t-e Test directory name (e.g. dot_test)"
   exit 1
}

while getopts "e:" opt
do
   case "$opt" in
      e ) TEST="$OPTARG" ;;
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

    echo $EXPECTED

    if [ -z "${DIFF}" ]
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

        echo "${YELLOW}Expected${NC}"
        cat $EXPECTED
        echo ""

        echo "${YELLOW}Diff${NC}"
        echo $DIFF
        echo ""
        break
    fi
done
