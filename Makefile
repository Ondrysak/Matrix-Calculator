CC = g++
CFLAGS = -Wall -Wno-long-long -ggdb -O0 -std=c++11 -pedantic

all: compile doc

run: compile
	./nankaond 20
doc: src/main.cpp src/c_wrapper.cpp src/c_standartmatrix.cpp src/c_dokmatrix.cpp src/main.cpp src/c_wrapper.h src/c_standartmatrix.h src/c_dokmatrix.h src/c_matrix.h
	doxygen;
	mv html doc;
compile: src/main.cpp src/c_wrapper.cpp src/c_standartmatrix.cpp src/c_dokmatrix.cpp src/c_wrapper.h src/c_standartmatrix.h src/c_dokmatrix.h src/c_matrix.h
	${CC} ${CFLAGS} src/main.cpp src/c_wrapper.cpp src/c_standartmatrix.cpp src/c_dokmatrix.cpp -o nankaond
clean:
	rm nankaond; rm -rf doc
