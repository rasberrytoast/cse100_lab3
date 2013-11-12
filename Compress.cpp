#include "HCTree.hpp"
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <stdio.h>
#include <stdlib.h>

#define INFILE_ARG 1
#define OUTFILE_ARG 2
#define MAX_NUM_SYMBOLS 256

int* getHCTreeHeader(char* inputFilename);

int main(int argc, char* argv[])
{
	char * inputFilename = argv[INFILE_ARG];
	char* outputFilename = argv[OUTFILE_ARG];

	int* hcTreeHeader;
	FILE* fpOut;

	printf("input file:%s\n", inputFilename);
	printf("output file:%s\n", outputFilename);

	hcTreeHeader = getHCTreeHeader(inputFilename);
/*
	HCTREE hcTree;
	hcTree.build(hcTreeHeader);
*/

	for(int i = 0; i < MAX_NUM_SYMBOLS; i++)
	{
		printf("char:%c count:%d", (char)i, hcTreeHeader[i]);
	}

//	compressFile(&hcTree, inputFilename, outputFilename);

	free(hcTreeHeader);
}

void compressFile(HCTREE* hcTree, int* hcTreeHeader, \
		char* inputFilename, char* outputFilename)
{
	FILE* fpIn = fOpen(inputFilename, "r");
	FILE* fpOut = fOpen(outputFilename, "w");
	int c;

	if(!fpIn)
	{
		perror("couldn't open input file");
		exit(EXIT_FAILURE);
	}

	//write header to compression file
	fwrite(hcTreeHeader, sizeof(int), sizeof(sizeof(int)*MAX_NUM_SYMBOLS),fpOut);

	//write compressed version of input file to compression file
	while((c=getc(fp))!= EOF)
	{
		hcTree.encode((char)c, outputFilename);
	}

	fclose(fpIn);
	fclose(fpOut);
}

int* getHCTreeHeader(char* inputFilename)
{
	int* hcTreeHeader = (int *)calloc((size_t)MAX_NUM_SYMBOLS, sizeof(int));
	FILE* fp = fopen((const char*)inputFilename, "r");
	int c;

	if(!fp)
	{
		perror("error reading inputfile");
		exit(EXIT_FAILURE);
	}

	while((c=getc(fp))!= EOF)
	{
		hcTreeHeader[c]++;
	}

	return hcTreeHeader;
}
