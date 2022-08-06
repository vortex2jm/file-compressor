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

  // List *list = CreateVoidList();

  // Tree *tree1, *tree2, *tree3, *tree4, *tree5;

  // tree1 = CreateInternalNode(CreateVoidTree(), CreateVoidTree(), 1);
  // tree2 = CreateInternalNode(CreateVoidTree(), CreateVoidTree(), 1);
  // tree3 = CreateInternalNode(CreateVoidTree(), CreateVoidTree(), 2);
  // tree4 = CreateInternalNode(CreateVoidTree(), CreateVoidTree(), 3);
  // tree5 = CreateInternalNode(CreateVoidTree(), CreateVoidTree(), 0);

  // ListPush(list, tree1);
  // ListPush(list, tree2);
  // ListPush(list, tree3);
  // ListPush(list, tree4);
  // ListPush(list, tree5);
  return 0;
}
