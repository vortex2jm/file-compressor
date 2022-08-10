#include "./include/binary_tree.h"
#include "./include/ordered_list.h"
#include "./include/table.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 

  long int fileSize = GetFileSize(argv[1]);

  int *frequencyTable = CreateFrequencyTable(argv[1]);

  List *list = CreateHuffmanList(frequencyTable);

  Huffman_Execute(list);

  unsigned char **table = CreateEncodeTable(list);

  unsigned char *text = ReadFile(argv[1], table, fileSize);
  
  long int encodedTextSize = 0;
  unsigned char *encodedText = EncodeText(table, text, fileSize, &encodedTextSize);

  CreateCompressedFile(encodedText, argv[1], frequencyTable, fileSize, encodedTextSize);

  DestructList(list);
  DestructEncodeTable(table);
  free(text);
  free(encodedText);

  return 0;
}
