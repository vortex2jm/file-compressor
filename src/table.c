#include "../include/table.h"
#include "../include/binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=======================================================================//
int *CreateFrequencyTable(char *fileWay)
{

  static int table[SIZE] = {0};
  unsigned char read_char = '\0';
  FILE *file = fopen(fileWay, "r");
  int index = 0;

  while (1)
  {
    if (feof(file))
    {
      table[read_char]--;
      break;
    }
    fscanf(file, "%c", &read_char);
    table[read_char] += 1;
  }
  return table;
}

//=======================================================================//
void PrintFrequencyTable(int *table)
{

  printf("\n====Tabela de frequencia====\n\n");

  for (int x = 0; x < SIZE; x++)
  {
    if (table[x])
    {
      printf("%d -> %d\n", x, table[x]);
    }
  }
}

//=======================================================================//
char **CreateEncodeTable(List *list)
{

  Tree *tree = GetTree(list);

  char **table = malloc(sizeof(char *) * SIZE);
  // A tabela possuirá uma coluna a mais que a altura da árvore, pois deve comportar o '\0' das strings
  for (int x = 0; x < SIZE; x++)
  {
    table[x] = calloc(TreeHeight(tree) + 1, sizeof(char));
  }

  FillEncodeTable(table, tree, "", TreeHeight(tree));
  return table;
}

//=======================================================================//
void PrintEncodeTable(char **table)
{
  printf("Tabela de codificacao======\n\n");
  for (int x = 0; x < SIZE; x++)
  {
    printf("%d -> %s\n", x, table[x]);
  }
}

//=======================================================================//
char *ReadFile(char *fileWay)
{

  FILE *file = fopen(fileWay, "r");
  long int tam;

  // aponta para o final do arquivo
  fseek(file, 0, SEEK_END);
  // Conta a quantidade de bytes que o arquivo possui do ínicio até a posição atual
  tam = ftell(file);
  // printf("Tamanho do arquivo = %ld\n", tam);

  char *text = calloc(tam, sizeof(char));
  // voltando o ponteiro para o inicio do arquivo
  fseek(file, 0, SEEK_SET);
  fscanf(file, "%[^EOF]", text);

  return text;
}

//=======================================================================//
char *EncodeText(char **encodeTable, char *text)
{

  long int size = 1;
  for (int x = 0; text[x] != '\0'; x++)
  {
    size += strlen(encodeTable[text[x]]);
  }

  char *code = calloc(size, sizeof(char));
  for (int x = 0; text[x] != '\0'; x++)
  {
    strcat(code, encodeTable[text[x]]);
  }
  return code;
}

//=======================================================================//
void CreateCompressedFile(unsigned char *text, char *name, int *frequencyTable)
{

  char fileName[50], noEx[45];
  sscanf(name, "%[^.]", noEx);
  sprintf(fileName, "%s.comp", noEx);

  FILE *file = fopen(fileName, "wb");
  if (!file)
  {
    printf("File creation failed!\n");
    exit(1);
  }

  // Procurar um jeito de escrever a arvore ou a tabela de codificação no arquivo
  fwrite(frequencyTable, sizeof(int), 256, file);
  //MODIFICADO
  unsigned long int encodedTextLenght = strlen(text);
  fwrite(&encodedTextLenght, sizeof(unsigned long int),1,file);

  unsigned char binary = 0;
  unsigned char aux = 1;

  for (int x = 0, y = 7; text[x] != '\0'; x++, y--)
  { 
    aux = 1;
    if (text[x] == '1')
    {
      aux = aux << y;
      binary = binary | aux;
    }
    if (y == 0)
    {
      fwrite(&binary, sizeof(unsigned char), 1, file);
      y = 8;
      binary = 0;
    }
  }

  if (strlen(text) % 8)
    fwrite(&binary, sizeof(unsigned char), 1, file);

  fclose(file);
}

//=======================================================================//
void UnzipFile(FILE *compressedFile, List *list, char *fileName)
{ 
  char name[50], noEx[45];
  sscanf(fileName, "%[^.]", noEx);
  sprintf(name, "%s.txt", noEx);

  //Abrindo arquivo descompactado
  FILE *unzipedFile = fopen(name, "w");

  Tree *tree = GetTree(list);
  unsigned char binary;
  unsigned char aux = 1;

  //MODIFICADO
  unsigned long int encodedTextLenght=0;
  fread(&encodedTextLenght, sizeof(unsigned long int), 1, compressedFile);
  printf("lenght = %ld\n", encodedTextLenght);

  unsigned long int byteCounter=0;

  while (fread(&binary, sizeof(unsigned char), 1, compressedFile))
  {
    aux = 1;
    
    for (int x = 7; x >= 0; x--)
    { 
      byteCounter++;
      aux = aux << x;

      if (aux & binary){
        tree = GetRightTree(tree);
      }
      else{
        tree = GetLeftTree(tree);
      }

      //se chegou no nó folha, imprime o caracter no arquivo
      if (!GetLeftTree(tree) && !GetRightTree(tree)){ 
        fprintf(unzipedFile, "%c", GetTreeChar(tree));
        tree = GetTree(list); //voltando para o nó raíz

        //se a quantidade de bits lidos for igual ao tamanho do texto
        //codificado, ele encerra o loop para evitar ler caracteres adicionais
        //caso a quantidade total não seja múltiplo de 8
        if(byteCounter == encodedTextLenght)break;
      }
      //resetando o valor de aux para realizar um novo bitshift
      aux = 1;
    }
  }
  printf("byteCounter = %ld\n", byteCounter);

  fclose(unzipedFile);
}