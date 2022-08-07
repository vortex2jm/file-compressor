#include "./include/binary_tree.h"
#include "./include/ordered_list.h"
#include "./include/table.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int *frequencyTable = CreateFrequencyTable(argv[1]);

  List *list = CreateHuffmanList(frequencyTable);

  Huffman_Execute(list);

  char **table = CreateEncodeTable(list);

  char *text = ReadFile(argv[1]);

  char *encodedText = EncodeText(table, text);

  CreateCompressedFile(encodedText, argv[1], frequencyTable);

  DestructList(list);
  DestructEncodeTable(table);
  free(text);
  free(encodedText);
  return 0;
}
