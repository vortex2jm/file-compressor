#include "binary_tree.h"
#include "ordered_list.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int *frequencyTable = CreateFrequencyTable(argv[1]);
  // PrintFrequencyTable(frequencyTable);
  
  List * list;

  list = CreateHuffmanList(frequencyTable);
  printf("Primeira lista===========\n\n");
  PrintList(list);

  list = Huffman_Execute(list);
  printf("Lista compactada===========\n\n");
  PrintList(list);

  char ** table;
  table = CreateEncodeTable(list);
  PrintEncodeTable(table);

  char * text;
  text = ReadFile(argv[1]);
  printf("texto do arquivo => %s\n", text);
  
  char * encodedText;
  encodedText = EncodeText(table, text);
  printf("texto codificado => %s\n", encodedText);

  CreateCompressedFile(encodedText, argv[1], frequencyTable);

  return 0;
}
