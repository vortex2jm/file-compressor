#include "table.h"
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

int *CreateFrequencyTable(char *fileWay) {

  static int table[SIZE] = {0};
  char read_char = '\0';
  FILE *file = fopen(fileWay, "r");
  int index = 0;

  while (1) {
    if (feof(file)) {
      table[read_char]--;
      break;
    }
    fscanf(file, "%c", &read_char);
    table[read_char]+=1;
  }
  return table;
}

void PrintFrequencyTable(int * table){

  printf("\n====Tabela de frequencia====\n\n");

  for(int x=0;x<SIZE;x++){
    printf("%d -> %d\n", x, table[x]);
  }
}

char ** CreateEncodeTable(List * list){

  Tree * tree = GetTree(list);

  char ** table = malloc(sizeof(char*)*SIZE);
  //A tabela possuirá uma coluna a mais que a altura da árvore, pois deve comportar o '\0' das strings
  for(int x=0;x<SIZE;x++){
    table[x] = calloc(TreeHeight(tree)+1, sizeof(char));
  }

  FillEncodeTable(table, tree,"",TreeHeight(tree));

} 