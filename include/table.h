#ifndef file_manager_h
#define file_manager_h
#include "ordered_list.h"
#include <stdio.h>
#define SIZE 256

int *CreateFrequencyTable(unsigned char *fileWay);

void PrintFrequencyTable(int * table);

unsigned char ** CreateEncodeTable(List * list);

void PrintEncodeTable(unsigned char ** table);

void DestructEncodeTable(unsigned char ** table);

unsigned char * ReadFile(unsigned char * fileWay, unsigned char ** table, long int fileSize);

unsigned char * EncodeText(unsigned char ** encodeTable, unsigned char * text, long int fileSize, long int * encodedTextSize);

void CreateCompressedFile(unsigned char * text, unsigned char * name, int * frequencyTable, long int fileSize, long int encodedTextSize);

void UnzipFile(FILE *compressedFile, List *list, unsigned char *fileName);

#endif // !file_manager_h