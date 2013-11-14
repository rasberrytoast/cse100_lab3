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
//xtra comment for commit
int* getHCTreeHeader(FILE*);
void uncompressFile(HCTREE*, int*,	FILE*, char*);

int main(int argc, char* argv[])
{
	char * inputFilename = argv[INFILE_ARG];
	char* outputFilename = argv[OUTFILE_ARG];
	FILE* fpIn = fopen((const char*)inputFilename, "r");
	
	int* hcTreeHeader;

	printf("input file:%s\n", inputFilename);
	printf("output file:%s\n", outputFilename);

	hcTreeHeader = getHCTreeHeader(fpIn);

	HCTREE hcTree;
	hcTree.build(&hcTree, hcTreeHeader);


	for(int i = 0; i < MAX_NUM_SYMBOLS; i++)
	{
		printf("char:%c count:%d", (char)i, hcTreeHeader[i]);
	}

	uncompressFile(&hcTree, hcTreeHeader, fpIn, outputFilename);

	free(hcTreeHeader);
	hcTree.deleteTree(&hcTree);
}

void uncompressFile(HCTREE* hcTree, int* hcTreeHeader, \
		FILE* fpIn, char* outputFilename)
{
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
		hcTree->decode(hcTree, (unsigned char)c, fpOut);
	}

	fclose(fpIn);
	fclose(fpOut);
}

int* getHCTreeHeader(FILE* fpIn)
{
	int* hcTreeHeader = (int *)calloc((size_t)MAX_NUM_SYMBOLS, sizeof(int));
	int c;

	if(!fpIn)
	{
		perror("error reading inputfile");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i< MAX_NUM_SYMBOLS; i++)
	{
		hcTreeHeader[i] = (byte)getc(fpIn);
	}

	return hcTreeHeader;
}
