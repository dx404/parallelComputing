#!/bin/bash
for i in {100..5000..1000}
do 
	./nBody_beta.out $i >> datav3.csv
	./nBody_beta.out $i >> datav3.csv
	./nBody_beta.out $i >> datav3.csv
	./nBody_beta.out $i >> datav3.csv
	./nBody_beta.out $i >> datav3.csv
	./nBody_beta.out $i >> datav3.csv
	./nBody_beta.out $i >> datav3.csv
done
