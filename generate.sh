#!/bin/bash

directories="toolkit game/rendering game/config game/character game/time .";
file="Makefile";
sources="";
objects="";
rules="";
compiler="gcc";
flags="-Wall -Wextra -O3 `sdl-config --cflags` -g";
libs="`sdl-config --libs` -lSDL_image";
exec="marioLight";

echo -n "Generating Makefile... ";

echo "all: ${exec}" > $file;

for i in `echo $directories`
do
    for j in ${i}/*.c
    do
        echo ${j} > temp
        filename=`sed -e 's/\.c//g' temp`;
        rm -rf temp;
        sources="${sources} ${j}";
        objects="${objects} ${filename}.o";
        echo -e "\n${filename}.o: ${filename}.c\n\t${compiler} ${filename}.c -c -o ${filename}.o ${flags}" >> $file
    done
done

echo -e "\n${exec}: ${objects}\n\t${compiler} ${objects} -o ${exec} ${flags} ${libs}" >> $file

echo -e "clean:\n\trm -rf ${objects} ${exec}" >> $file

echo "done";