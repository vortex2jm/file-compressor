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
void FillEncodeTable(unsigned char **table, Tree *tree, unsigned char *code, int treeHeight)
{
  if (!GetLeftTree(tree) && !GetRightTree(tree))
  {
    strcpy(table[GetTreeChar(tree)], code);
    return;
  }

  unsigned char left[treeHeight], right[treeHeight];
  strcpy(left, code);
  strcpy(right, code);
  strcat(left, "0");
  strcat(right, "1");

  FillEncodeTable(table, GetLeftTree(tree), left, treeHeight);
  FillEncodeTable(table, GetRightTree(tree), right, treeHeight);
}

//=======================================================================//
unsigned char **CreateEncodeTable(List *list) {
  Tree *tree = GetTree(list);

  unsigned char **table = malloc(sizeof(unsigned char *) * SIZE);
  // A tabela possuirá uma coluna a mais que a altura da árvore, pois deve
  // comportar o '\0' das strings
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
unsigned char *ReadFile(unsigned char *fileWay, long int fileSize) {
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
  
  //Percorrendo os bytes do arquivo e adicionando o código da tabela de codificação
  //na stream codificada
  long int encodedTextIndex = 0, codeIndex=0;
  for(int x=0; x<fileSize;x++){
    while(encodeTable[text[x]][codeIndex] != '\0'){   
      code[encodedTextIndex] = encodeTable[text[x]][codeIndex];
      encodedTextIndex++;
      codeIndex++;
    }
    codeIndex=0;
  }
  return code;
}

//=======================================================================//
void CreateCompressedFile(unsigned char *text, unsigned char *name, int *frequencyTable, long int encodedTextSize){
  unsigned char fileName[50], noEx[45], ext[5];
  sscanf(name, "%[^.]%s", noEx, ext);
  sprintf(fileName, "%s.comp", noEx);

  FILE *file = fopen(fileName, "wb");
  if (!file) {
    printf("File creation failed!\n");
    exit(1);
  }

  unsigned long int encodedTextLenght = encodedTextSize;
  fwrite(frequencyTable, sizeof(int), 256, file); //tabela de frequencia
  fwrite(ext, sizeof(unsigned char), 5, file);  //nome da extensão
  fwrite(&encodedTextLenght, sizeof(unsigned long int), 1, file); //stream codificada

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
  //Tratando final da stream que não completa 1 byte
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
