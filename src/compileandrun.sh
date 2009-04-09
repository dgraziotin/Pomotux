#!/bin/bash
rm pomotux.db
litesql-gen pomotuxdatabase.xml
make clean
make
./pomotux
