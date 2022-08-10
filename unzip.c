#include "./include/table.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 
  //Abrindo o arquivo compactado
  FILE * file = fopen(argv[1],"rb");
  int frequencyTable[256];

  //Lendo tabela de frequência que está no cabeçalho do arquivo
  fread(frequencyTable,sizeof(int),256,file);

  //Recriando a árvore binária a partir da tabela de frequência
  List * list = CreateHuffmanList(frequencyTable);
  Huffman_Execute(list);

  //Descompactando o arquivo e escrevendo o arquivo original
  UnzipFile(file, list, argv[1]);
  
  fclose(file);

  //Liberando memória alocada
  DestructList(list);

  return 0;
}