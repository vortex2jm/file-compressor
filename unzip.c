#include "./include/table.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE * file = fopen(argv[1],"rb");
  int frequencyTable[256];

  fread(frequencyTable,sizeof(int),256,file);
  PrintFrequencyTable(frequencyTable);

  return 0;
}