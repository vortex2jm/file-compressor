#include "../include/table.h"
#include "../include/binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=======================================================================//
int *CreateFrequencyTable(unsigned char *fileWay) {
  static int table[SIZE] = {0};
  unsigned char read_char = '\0';
  FILE *file = fopen(fileWay, "rb");
  int index = 0;

  while (fread(&read_char, sizeof(unsigned char), 1, file)) {
    table[read_char] += 1;
  }
  fclose(file);

  return table;
}

//=======================================================================//
void PrintFrequencyTable(int *table) {
  printf("\n====Tabela de frequencia====\n\n");
  for (int x = 0; x < SIZE; x++) {
    if (table[x]) {
      printf("%d -> %d\n", x, table[x]);
    }
  }
}

//=======================================================================//
unsigned char **CreateEncodeTable(List *list) {
  Tree *tree = GetTree(list);

  unsigned char **table = malloc(sizeof(unsigned char *) * SIZE);
  // A tabela possuirá uma coluna a mais que a altura da árvore, pois deve c
  // mportar o '\0' das strings
  for (int x = 0; x < SIZE; x++) {
    table[x] = calloc(TreeHeight(tree) + 1, sizeof(unsigned char));
  }

  FillEncodeTable(table, tree, "", TreeHeight(tree));
  return table;
}

//=======================================================================//
void PrintEncodeTable(unsigned char **table) {
  printf("Tabela de codificacao======\n\n");
  for (int x = 0; x < SIZE; x++) {
    printf("%d -> %s\n", x, table[x]);
  }
}

//=======================================================================//
void DestructEncodeTable(unsigned char **table) {
  if (table) {
    for (int x = 0; x < SIZE; x++) {
      if (table[x])
        free(table[x]);
    }
    free(table);
  }
}

//=======================================================================//
unsigned char *ReadFile(unsigned char *fileWay, unsigned char **table,
                        long int fileSize) {
  FILE *file = fopen(fileWay, "rb");

  unsigned char *text = calloc(fileSize, sizeof(unsigned char));

  long int counter = 0;
  unsigned char byte;
  while (fread(&byte, sizeof(unsigned char), 1, file)) {
    text[counter] = byte;
    counter++;
  }

  fclose(file);

  return text;
}

//=======================================================================//
unsigned char *EncodeText(unsigned char **encodeTable, unsigned char *text,
                          long int fileSize, long int *encodedTextSize) {
  long int size = 0;

  for (int x = 0; x < fileSize; x++) {
    size += strlen(encodeTable[text[x]]);
  }
  *encodedTextSize = size;

  unsigned char *code = calloc(size+1, sizeof(unsigned char));
  
  long int encodedTextIndex = 0, codeIndex=0;
  for(int x=0; x<fileSize;x++){
    while(encodeTable[text[x]][codeIndex] != '\0'){

      code[encodedTextIndex] = encodeTable[text[x]][codeIndex];
      encodedTextIndex++;
      codeIndex++;
    }
    codeIndex=0;
  }

  /*O trecho abaixo foi removido pois a função strcat em loop 
  estava deixando o código ineficiente. Em arquivos maiores, a função 
  precisava percorrer strings muito grandes para concatenar*/

  /*O trecho que substitui insere os bytes por acesso direto ao
  índice do vetor, o que torna o programa mais rápido. Utilizando a strcat,
  demorava cerca de 10 minutos para montar a stream codificada de um arquivo
  de 4MB. Com o acesso direto demora menos de 1 segundo*/

  // for (int x = 0; x < fileSize; x++) {
  //   strcat(code, encodeTable[text[x]]);
  // }

  return code;
}

//=======================================================================//
void CreateCompressedFile(unsigned char *text, unsigned char *name,
                          int *frequencyTable, long int fileSize,
                          long int encodedTextSize) {
  unsigned char fileName[50], noEx[45], ext[5];
  sscanf(name, "%[^.]%s", noEx, ext);
  sprintf(fileName, "%s.comp", noEx);

  FILE *file = fopen(fileName, "wb");
  if (!file) {
    printf("File creation failed!\n");
    exit(1);
  }

  unsigned long int encodedTextLenght = encodedTextSize;
  fwrite(frequencyTable, sizeof(int), 256, file);
  fwrite(ext, sizeof(unsigned char), 5, file);
  fwrite(&encodedTextLenght, sizeof(unsigned long int), 1, file);

  unsigned char binary = 0;
  unsigned char aux = 1;

  for (int x = 0, y = 7; x < encodedTextSize; x++, y--) {
    aux = 1;
    if (text[x] == '1') {
      aux = aux << y;
      binary = binary | aux;
    }
    if (y == 0) {
      fwrite(&binary, sizeof(unsigned char), 1, file);
      y = 8;
      binary = 0;
    }
  }
  // if(strlen(text) % 8)
  if (encodedTextSize % 8)
    fwrite(&binary, sizeof(unsigned char), 1, file);
  fclose(file);
}

//=======================================================================//
void UnzipFile(FILE *compressedFile, List *list, unsigned char *fileName) {
  unsigned char name[50], noEx[45];
  sscanf(fileName, "%[^.]", noEx);

  Tree *tree = GetTree(list);
  unsigned char binary;
  unsigned char aux = 1;

  unsigned char ext[5];
  fread(ext, sizeof(unsigned char), 5, compressedFile);

  // Colocando o nome da extensão no arquivo
  sprintf(name, "%s%s", noEx, ext);
  // Abrindo arquivo descompactado
  FILE *unzipedFile = fopen(name, "wb");

  unsigned long int encodedTextLenght = 0;
  fread(&encodedTextLenght, sizeof(unsigned long int), 1, compressedFile);

  unsigned long int byteCounter = 0;
  unsigned char writeChar = '\0';

  while (fread(&binary, sizeof(unsigned char), 1, compressedFile)) {
    aux = 1;
    for (int x = 7; x >= 0; x--) {
      byteCounter++;
      aux = aux << x;
      if (aux & binary) {
        tree = GetRightTree(tree);
      } else {
        tree = GetLeftTree(tree);
      }
      // se chegou no nó folha, imprime o caracter no arquivo
      if (!GetLeftTree(tree) && !GetRightTree(tree)) {
        writeChar = GetTreeChar(tree);
        fwrite(&writeChar, sizeof(unsigned char), 1, unzipedFile);
        tree = GetTree(list); // voltando para o nó raíz

        // se a quantidade de bits lidos for igual ao tamanho do texto
        // codificado, ele encerra o loop para evitar ler caracteres adicionais
        // caso a quantidade total não seja múltiplo de 8
        if (byteCounter == encodedTextLenght)
          break;
      }
      // resetando o valor de aux para realizar um novo bitshift
      aux = 1;
    }
  }
  fclose(unzipedFile);
}

//=======================================================================//
long int GetFileSize(char * fileName){

  FILE * file = fopen(fileName,"rb");
  fseek(file,0,SEEK_END);
  long int fileSize = ftell(file);
  fseek(file,0,SEEK_SET);
  fclose(file);

  return fileSize;
}
