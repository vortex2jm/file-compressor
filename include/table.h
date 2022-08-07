#ifndef file_manager_h
#define file_manager_h
#include "ordered_list.h"
#include <stdio.h>
#define SIZE 256

int *CreateFrequencyTable(char *fileWay);

void PrintFrequencyTable(int * table);

char ** CreateEncodeTable(List * list);

void PrintEncodeTable(char ** table);

void DestructEncodeTable(char ** table);

char * ReadFile(char * fileWay);

char * EncodeText(char ** encodeTable, char * text);

void CreateCompressedFile(unsigned char * text, char * name, int * frequencyTable);

void UnzipFile(FILE *compressedFile, List *list, char *fileName);

#endif // !file_manager_h