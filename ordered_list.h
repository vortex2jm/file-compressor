#ifndef list_h
#define list_h
#include "binary_tree.h"

typedef struct list List;

List *CreateVoidList();

List *ListPush(List *list, Tree *tree);

void PrintList(List *list);

Tree *RemoveFromList(List *list, int weight);

void DeleteList(List *list);

List * CreateHuffmanList(int * frequencyTable);

List * Huffman_Execute(List * list);

Tree * GetTree(List * list);

#endif // !list_h
