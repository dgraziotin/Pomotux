#!/bin/bash
UTILS_DIR=utils
SRC_DIR=src
BIN_DIR=.
DB_DIR=$BIN_DIR

rm -f pomotux
rm -f pomotux.db
cd ${SRC_DIR} 
litesql-gen pomotuxdatabase.xml 
make clean
make
mv pomotux ..
cd ..
./pomotux
