rm -rf pomotuxTEST.db
cxxtestgen.py --error-printer  -o testpomotux.cpp *.h
g++ ../src/pomotuxdatabase.cpp ../src/activity.cpp ../src/activityinventorysheet.cpp ../src/todotodaysheet.cpp testpomotux.cpp -llitesql -o testpomotux
./testpomotux
