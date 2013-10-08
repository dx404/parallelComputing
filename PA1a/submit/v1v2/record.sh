#!/bin/bash
make clean
make
for i in {0..7}
do 
	./main.out >> data.csv
done
cat data.csv


