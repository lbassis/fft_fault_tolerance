# C compiler
CC = g++ -g -std=c++14
FFTW3 = -lfftw3 -lm

destDir = /tmp/fftw_cpp

all: gen_bin gen_data mv_bin

gen_bin: fftw.cpp
	$(CC) fftw.cpp -o fftw $(FFTW3)

gen_data: gen_bin
	python ../../matrix_creator.py ../../images/big.jpg
	./fftw matrix.txt golden.txt

mv_bin: gen_data
	mkdir -p $(destDir)
	mv matrix.txt $(destDir)
	mv ./fftw $(destDir)
	mv ./golden.txt $(destDir)
	cp ./fftw.conf $(destDir)
	@echo "All Done, executables should be in the $(destDir)"
