#!/bin/bash
litesql-gen pomotuxdatabase.xml
g++ pomotuxdatabase.cpp main.cpp -llitesql -o pomotux
./pomotux
