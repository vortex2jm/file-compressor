#include "./include/table.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 
  //Abrindo o arquivo compactado
  FILE * file = fopen(argv[1],"rb");
  int frequencyTable[256];

  //lendo tabela de frequência
  fread(frequencyTable,sizeof(int),256,file);
  PrintFrequencyTable(frequencyTable);

  //Recriando a árvore binária a partir da tabela de frequência
  List * list = CreateHuffmanList(frequencyTable);
  printf("Primeira lista===========\n\n");
  PrintList(list);

  Huffman_Execute(list);
  printf("Lista compactada===========\n\n");
  PrintList(list);

  UnzipFile(file, list, argv[1]);

  return 0;
}