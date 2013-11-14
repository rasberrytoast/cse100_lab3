#include "HCTree.hpp"
#include "HCTree.cpp"
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <stdio.h>
#include <stdlib.h>

#define INFILE_ARG 1
#define OUTFILE_ARG 2
#define MAX_NUM_SYMBOLS 256

int* getHCTreeHeader(char* inputFilename);
void compressFile(HCTREE*, int*,	char*, char*);

int main(int argc, char* argv[])
{
	char * inputFilename = argv[INFILE_ARG];
	char* outputFilename = argv[OUTFILE_ARG];
	
	int* hcTreeHeader;

	printf("input file:%s\n", inputFilename);
	printf("output file:%s\n", outputFilename);

	hcTreeHeader = getHCTreeHeader(inputFilename);

	HCTREE hcTree;
	hcTree.build(&hcTree, hcTreeHeader);


	for(int i = 0; i < MAX_NUM_SYMBOLS; i++)
	{
		printf("char:%c count:%d", (char)i, hcTreeHeader[i]);
	}

	compressFile(&hcTree, hcTreeHeader, inputFilename, outputFilename);

	free(hcTreeHeader);
	hcTree.deleteTree(&hcTree);
}

void compressFile(HCTREE* hcTree, int* hcTreeHeader, \
		char* inputFilename, char* outputFilename)
{
	FILE* fpIn = fopen((const char*)inputFilename, "r");
	FILE* fpOut = fopen(outputFilename, "w");
	int c;

	if(!fpIn)
	{
		perror("couldn't open input file");
		exit(EXIT_FAILURE);
	}

	//write compressed version of input file to compression file
	while((c=getc(fpIn))!= EOF)
	{
		hcTree->encode(hcTree, (unsigned char)c, fpOut);
	}

	fclose(fpIn);
	fclose(fpOut);
}

int* getHCTreeHeader(char* inputFilename)
{
	int* hcTreeHeader = (int *)calloc((size_t)MAX_NUM_SYMBOLS, sizeof(int));
	FILE* fpIn = fopen((const char*)inputFilename, "r");
	int c;

	if(!fpIn)
	{
		perror("error reading inputfile");
		exit(EXIT_FAILURE);
	}

	while((c = getc(fpIn)) != EOF)
	{
		hcTreeHeader[(byte)c]++;
	}

	fclose(fpIn);
	return hcTreeHeader;
}
