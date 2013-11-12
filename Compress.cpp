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

	printf("input file:%s\n", inputFilename);
	printf("output file:%s\n", outputFilename);

	hcTreeHeader = getHCTreeHeader(inputFilename);

	for(int i = 0; i < MAX_NUM_SYMBOLS; i++)
	{
		printf("char:%c count:%d", (char)i, hcTreeHeader[i]);
	}

	free(hcTreeHeader);



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
