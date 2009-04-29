#!/bin/sh

ROOT_DIR=`pwd`
UTILS_DIR=$ROOT_DIR/utils
SRC_DIR=$ROOT_DIR/src
BIN_DIR=$ROOT_DIR
DB_DIR=$BIN_DIR
TEST_DIR=$ROOT_DIR/test


rm -rf ${DB_DIR}/pomotuxTEST.db ${BIN_DIR}/testpomotux
cd $TEST_DIR
cxxtestgen.py --error-printer  -o testpomotux.cpp *.h
g++ ${SRC_DIR}/pomotuxdatabase.cpp ${SRC_DIR}/activity.cpp ${SRC_DIR}/activityinventorysheet.cpp ${SRC_DIR}/todotodaysheet.cpp ${TEST_DIR}/testpomotux.cpp -llitesql -o ${BIN_DIR}/testpomotux
cd $BIN_DIR
$BIN_DIR/testpomotux
