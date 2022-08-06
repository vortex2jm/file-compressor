#ifndef file_manager_h
#define file_manager_h
#include "ordered_list.h"
#define SIZE 256

int *CreateFrequencyTable(char *fileWay);

void PrintFrequencyTable(int * table);

char ** CreateEncodeTable(List * list);

#endif // !file_manager_h