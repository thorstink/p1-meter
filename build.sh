#/bin/sh
cmake -S $1 -B $1/build
make -C $1/build/
