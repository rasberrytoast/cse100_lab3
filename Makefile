# A simple makefile for CSE 100 P3

CC=g++
CXXFLAGS=-g#-std=c++11 -g
LDFLAGS=-g

all: compress uncompress

compress: BitInputStream.o BitOutputStream.o HCNode.o HCTree.o Compress.o

uncompress: BitInputStream.o BitOutputStream.o HCNode.o HCTree.o

HCTree.o: BitInputStream.hpp BitOutputStream.hpp HCNode.hpp HCTree.hpp

Compress.o: Compress.cpp

HCNode.o: HCNode.hpp

BitOutputStream.o: BitOutputStream.hpp

BitInputStream.o: BitInputStream.hpp

clean:
	rm -f compress uncompress *.o core*

