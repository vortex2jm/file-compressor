#ifndef file_manager_h
#define file_manager_h
#include "ordered_list.h"
#define SIZE 256

int *CreateFrequencyTable(char *fileWay);

void PrintFrequencyTable(int * table);

char ** CreateEncodeTable(List * list);

void PrintEncodeTable(char ** table);

char * ReadFile(char * fileWay);

char * EncodeText(char ** encodeTable, char * text);

void CompressText(unsigned char * text, char * name);

#endif // !file_manager_h