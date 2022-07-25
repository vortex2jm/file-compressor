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

  Cell *current = list->first, *previous = NULL;
  Cell *newCell = malloc(sizeof(Cell));
  newCell->tree = tree;
  newCell->next = NULL;

  // se a lista estiver vazia, insere na primeira posição(que também será a últ
  // ma)
  if (!list->first) {
    printf("inserindo a primeira posicao\n");
    list->first = newCell;
    list->last = newCell;
    return list;
  }
  // Caso contrário percorre a lista
  while (current) {

    if(TreeWeight(tree) < TreeWeight(current->tree)){

      if(current == list->first){

        newCell->next = current;
        list->first = newCell;
      }
      else{

        previous->next = newCell;
        newCell->next = current;
      }
      break;
    }
    if(current == list->last){

      current->next = newCell;
      list->last = newCell;
      break;
    }
    previous = current;
    current = current->next;
  }
  return list;
}

void PrintList(List *list){

  Cell * current = list->first;

  printf("entrou na funcao de print\n");

  while(current){

    printf("peso -> %d\n",TreeWeight(current->tree));
    
    current = current->next;
  }
}

Tree *RemoveFromList(List *list, int weight);

void DeleteList(List *list);