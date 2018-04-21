# C compiler
CC = gcc -lm -g

destDir = /tmp/cooley_c

all: gen_bin gen_data mv_bin

gen_bin: cooley_tukey.c
	$(CC) cooley_tukey.c -o c

gen_data: gen_bin
	python ../../matrix_creator.py ../../images/big.jpg
	./c matrix.txt golden.txt

mv_bin: gen_data
	mkdir -p $(destDir)
	mv matrix.txt $(destDir)
	mv c $(destDir)
	mv golden.txt $(destDir)
	cp c.conf $(destDir)
	@echo "All Done, executables should be in the $(destDir)"
