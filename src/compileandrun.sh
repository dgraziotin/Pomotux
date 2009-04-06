#!/bin/bash
litesql-gen pomotuxdatabase.xml
g++ iactivity.hpp iactivityinventorysheet.hpp itodotodaysheet.hpp
g++ pomotuxdatabase.cpp main.cpp iactivity.cpp iactivityinventorysheet.cpp itodotodaysheet.cpp -llitesql -o pomotux
./pomotux
