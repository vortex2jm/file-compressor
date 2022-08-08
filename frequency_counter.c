#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int amount_array[256] = {0};
  char file_way[50], read_char;

  sprintf(file_way, "./%s", argv[1]);
  FILE *file = fopen(file_way, "r");

  while (1) {

    if (feof(file)) {
      amount_array[read_char]--;
      break;
    }
    fscanf(file, "%c", &read_char);
    amount_array[read_char]++;
  }

  for (int i = 0; i < 256; i++) {
    printf("%d\n", amount_array[i]);
  }

  return 0;
}
