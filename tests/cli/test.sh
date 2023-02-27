#! /bin/bash

CC="gcc"
CFLAGS="-Wall -Wextra -Werror"
TEST_DIR="tests/cli/"
SCR_FILE="./srcs/parse.c"
TEST_FILE="./${TEST_DIR}/cli.c"
INCLUDES="./includes"
NAME="test_cli"

PATHNAME="TODO"
PID=`pgrep code  | head -1`

GET_VALUE_RES=

# $1=Input to analyse $2=Key from the input
function get_value()
{
    GET_VALUE_RES=`echo "${1}" | grep "${2}" | sed "s/^.*: //"`
}

OPTS_RES=
OPTS_TXT="OPTS: "
PID_RES=
PID_TXT="PID: "
PATH_RES=
PATH_TXT="PATH: "

# $1=Result of the command
function get_values()
{
    get_value "${1}" ${OPTS_TXT}
    OPTS_RES=${GET_VALUE_RES}

    get_value "${1}" ${PID_TXT}
    PID_RES=${GET_VALUE_RES}

    get_value "${1}" ${PATH_TXT}
    PATH_RES=${GET_VALUE_RES}
}

CHECK_RES=

# $1=Expected opts $2=Expected pid $3=Expected path
function check_values()
{
    if [ ! ${1} == ${OPTS_RES} ] \
    || [ ! ${2} == ${PID_RES} ] \
    || [ ! ${3} == ${PATH_RES} ] ; then
        CHECK_RES=0
    else
        CHECK_RES=1
    fi
}

HAS_ERROR=0

# $1=Test nb $2=Command
function print_res()
{
    echo -n $'\033[36m'"Test #${1}:"$'\033[33m'"'${CMD}'" $'\033[0m'
    if [ $CHECK_RES -eq 1 ] ; then
        echo $'\033[32m'"[PASS]"$'\033[0m'
    else
        echo $'\033[31m'"[FAIL]"$'\033[0m'
        HAS_ERROR=1
    fi
}

$CC -o $NAME $CFLAGS $SCR_FILE $TEST_FILE -I${INCLUDES}

CMD="./a.out -p $PID"
get_values "`${CMD}`"
check_values "1" "$PID" "(null)"
print_res "1" "${CMD}"

CMD="./a.out -P $PATHNAME"
get_values "`${CMD}`"
check_values "2" "0" "(null)"
print_res "2" "${CMD}"

CMD="./a.out -V"
get_values "`${CMD}`"
check_values "4" "0" "(null)"
print_res "3" "${CMD}"

CMD="./a.out -h"
get_values "`${CMD}`"
check_values "8" "0" "(null)"
print_res "4" "${CMD}"

CMD="./a.out -c"
get_values "`${CMD}`"
check_values "16" "0" "(null)"
print_res "5" "${CMD}"

CMD="./a.out -z"
get_values "`${CMD}`"
check_values "32" "0" "(null)"
print_res "6" "${CMD}"

CMD="./a.out -Z"
get_values "`${CMD}`"
check_values "64" "0" "(null)"
print_res "6" "${CMD}"

rm $NAME

exit $HAS_ERROR
