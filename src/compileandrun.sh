#!/bin/bash
litesql-gen pomotuxdatabase.xml
g++ pomotuxdatabase.cpp main.cpp iactivity.cpp iactivityinventorysheet.cpp itodotodaysheet.cpp -llitesql -o pomotux
./pomotux
