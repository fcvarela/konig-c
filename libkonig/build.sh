#!/bin/bash

rm -rf build
mkdir build
cd build
cmake .. -Wno-dev
make
cd ..

gcc -o test-linked test-linked.c -lkonig -Lbuild -Isrc

