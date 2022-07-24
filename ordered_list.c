#include "ordered_list.h"
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cell Cell;

struct list {

  Cell *first;
  Cell *last;
};

struct cell {

  Tree *tree;
  Cell *next;
};

List *CreateVoidList() {

  List *list = malloc(sizeof(List));
  list->first = NULL;
  list->last = NULL;

  return list;
}

List *ListPush(List *list, Tree *tree) {

  Cell *current = list->first;
  Cell *newCell = malloc(sizeof(Cell));
  newCell->tree = tree;
  newCell->next = NULL;

  // se a lista estiver vazia, insere na primeira posição(que também será a últ
  // ma)
  if (!list->first) {

    list->first = newCell;
    list->last = newCell;
    return list;
  }

  // Caso contrário percorre a lista
  while (current) {

    if (!current->next) {

    } else if (TreeWeight(current->next->tree) > TreeWeight(tree)) {
    }

    current = current->next;
  }

  return list;
}

void PrintList(List *list);

Tree *RemoveFromList(List *list, int weight);

void DeleteList(List *list);
