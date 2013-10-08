#!/bin/bash
gcc -O3 -o nBody_best.out nBody_best.c -lm
for i in {0,1,2,10,100,1000,10000}
do 
	./nBody_best.out 4 $i >> check.csv
done
