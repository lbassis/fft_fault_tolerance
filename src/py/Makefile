destDir = /tmp/cooley_py

all: gen_data mv_bin

gen_data: 
	python ../../matrix_creator.py ../../images/big.jpg
	python cooley_tukey.py matrix.txt golden.txt


mv_bin: gen_data
	mkdir -p $(destDir)
	mv matrix.txt $(destDir)
	mv cooley_tukey.py $(destDir)
	mv golden.txt $(destDir)
	cp py.conf $(destDir)
	@echo "All Done, executables should be in the $(destDir)"
