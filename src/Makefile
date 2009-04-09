#
# Makefile for 'pomotux'.
#
# Type 'make' or 'make pomotux' to create the executable.
# Type 'make clean' to delete all temporaries.
#

CC = g++

# build target specs
CFLAGS = -g -Wall -DDEBUG 
OUT_DIR = .
LIBS = -llitesql

# first target entry is the target invoked when typing 'make'
default: all

all: $(OUT_DIR)/activity.cpp.o $(OUT_DIR)/activityinventorysheet.cpp.o $(OUT_DIR)/main.cpp.o $(OUT_DIR)/pomotuxdatabase.cpp.o $(OUT_DIR)/todotodaysheet.cpp.o
	$(CC) $(CFLAGS) -o pomotux $(OUT_DIR)/activity.cpp.o $(OUT_DIR)/activityinventorysheet.cpp.o $(OUT_DIR)/main.cpp.o $(OUT_DIR)/pomotuxdatabase.cpp.o $(OUT_DIR)/todotodaysheet.cpp.o $(LIBS)

$(OUT_DIR)/activity.cpp.o: activity.cpp pomotuxdatabase.hpp
	$(CC) $(CFLAGS) -o $(OUT_DIR)/activity.cpp.o -c activity.cpp

$(OUT_DIR)/activityinventorysheet.cpp.o: activityinventorysheet.cpp \
  pomotuxdatabase.hpp
	$(CC) $(CFLAGS) -o $(OUT_DIR)/activityinventorysheet.cpp.o -c activityinventorysheet.cpp

$(OUT_DIR)/main.cpp.o: main.cpp pomotuxdatabase.hpp
	$(CC) $(CFLAGS) -o $(OUT_DIR)/main.cpp.o -c main.cpp

$(OUT_DIR)/pomotuxdatabase.cpp.o: pomotuxdatabase.cpp pomotuxdatabase.hpp
	$(CC) $(CFLAGS) -o $(OUT_DIR)/pomotuxdatabase.cpp.o -c pomotuxdatabase.cpp

$(OUT_DIR)/todotodaysheet.cpp.o: todotodaysheet.cpp pomotuxdatabase.hpp
	$(CC) $(CFLAGS) -o $(OUT_DIR)/todotodaysheet.cpp.o -c todotodaysheet.cpp

clean:
	rm -f pomotux $(OUT_DIR)/*.o

profile:
	gprof mde > profile.txt; ./gprof2dot.py profile.txt | dot -Tpng -o profile.png
