# C compiler
CC = g++ -g

destDir = /tmp/cooley_cpp

all: gen_bin gen_data mv_bin

gen_bin: cooley_tukey.cpp
	$(CC) cooley_tukey.cpp -o cpp

gen_data: gen_bin
	./cpp ../../matrix.txt ./golden.txt

mv_bin: gen_data
	mkdir -p $(destDir)
	cp ../../matrix.txt $(destDir)
	mv ./cpp $(destDir)
	mv ./golden.txt $(destDir)
	cp ./cpp.conf $(destDir)
	@echo "All Done, executables should be in the $(destDir)"
