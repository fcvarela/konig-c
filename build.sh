#!/bin/bash

rm -rf build
mkdir build
cd build
cmake .. -Wno-dev
make
cd ..

gcc -o konig main.c -lkonig -Lbuild -Isrc
