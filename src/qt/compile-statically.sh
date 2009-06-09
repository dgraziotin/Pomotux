#!/bin/bash
ln -s `gcc -print-file-name=libstdc++.a`
ln -s `gcc -print-file-name=libsqlite3.a`
ln -s `gcc -print-file-name=liblitesql.a`
qmake-static Pomotux.pro-static
make clean
cp main.cpp main.cpp-shared
cp main.cpp-static main.cpp
make
cp main.cpp-shared main.cpp