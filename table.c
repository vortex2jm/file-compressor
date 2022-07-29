#include "table.h"
#include <stdio.h>
#include <stdlib.h>

int *CreateFrequencyTable(char *fileWay) {

  static int table[256] = {0};
  char read_char = '\0';
  FILE *file = fopen(fileWay, "r");

  while (1) {
    if (feof(file)) {
      table[read_char]--;
      break;
    }

    fscanf(file, "%c", &read_char);
    table[read_char]++;
  }
  return table;
}
