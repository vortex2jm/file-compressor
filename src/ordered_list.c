#include "../include/ordered_list.h"
#include "../include/table.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cell Cell;

struct list
{
  Cell *first;
  Cell *last;
};

struct cell
{
  Tree *tree;
  Cell *next;
};

//=======================================================================//
List *CreateVoidList()
{
  List *list = malloc(sizeof(List));
  list->first = NULL;
  list->last = NULL;

  return list;
}

//=======================================================================//
List *ListPush(List *list, Tree *tree)
{
  Cell *current = list->first, *previous = NULL;
  Cell *newCell = malloc(sizeof(Cell));
  newCell->tree = tree;
  newCell->next = NULL;

  // se a lista estiver vazia, insere na primeira posição(que também será a últ
  // ma)
  if (!list->first)
  {
    list->first = newCell;
    list->last = newCell;
    return list;
  }
  // Caso contrário percorre a lista e insere na posição ordenada
  while (current)
  {
    if (TreeWeight(tree) < TreeWeight(current->tree))
    {
      if (current == list->first)
      {
        newCell->next = current;
        list->first = newCell;
      }
      else
      {
        previous->next = newCell;
        newCell->next = current;
      }
      break;
    }
    if (current == list->last)
    {
      current->next = newCell;
      list->last = newCell;
      break;
    }
    previous = current;
    current = current->next;
  }
  return list;
}

//=======================================================================//
void PrintList(List *list)
{
  Cell *current = list->first;
  while (current)
  {
    PrintTree(current->tree);
    printf("\n");
    current = current->next;
  }
}

//=======================================================================//
void DestructList(List *list){

  if(list){
    Cell * current = list->first, *aux;
    while(current){
      aux = current->next;
      DestructTree(current->tree);
      free(current);
      current = aux;
    }
    free(list);
  }
}

//=======================================================================//
List *CreateHuffmanList(int *frequencyTable)
{
  // Criando lista vazia
  List *list = CreateVoidList();

  // declarando variáveis auxiliares
  Tree *tree;
  unsigned char character;
  int weight;

  // preenchendo lista com árvores criadas a partir da tabela de frequência
  for (int x = 0; x < SIZE; x++)
  {
    if (frequencyTable[x])
    {
      tree = CreateLeafNode(CreateVoidTree(), CreateVoidTree(), frequencyTable[x], (unsigned char)x);
      list = ListPush(list, tree);
    }
  }
  return list;
}

//=======================================================================//
List *Huffman_Execute(List *list)
{
  // retorna null caso não exista a lista ou ela esteja vazia
  if (!list)
    return NULL;

  // variaveis auxiliares
  Cell *current = list->first;
  Tree *treeCurrent, *treeNext, *newTree;
  int weightSum = 0;

  // enquanto existir duas células na lista, aplicará o algoritmo de huffman
  while (current)
  {
    if (current->next)
    {
      // Criando nova arvore a partir das duas antigas
      treeCurrent = current->tree;
      treeNext = current->next->tree;
      weightSum = TreeWeight(treeCurrent) + TreeWeight(treeNext);
      newTree = CreateInternalNode(treeCurrent, treeNext, weightSum);

      // reencadeando a lista
      list->first = current->next->next;

      // liberando as celulas vazias
      free(current->next);
      free(current);

      // inserindo a nova arvore na lista
      list = ListPush(list, newTree);

      current = list->first;
    }
    else
      current = current->next;
  }
  return list;
}

//=======================================================================//
Tree *GetTree(List *list)
{
  return list->first->tree;
}