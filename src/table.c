#include "../include/table.h"
#include "../include/binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=======================================================================//
int *CreateFrequencyTable(unsigned char *fileWay)
{
  static int table[SIZE] = {0};
  unsigned char read_char = '\0';
  FILE *file = fopen(fileWay, "rb");
  int index = 0;

  // while (1)
  // {
  //   if (feof(file))
  //   {
  //     table[read_char]--;
  //     break;
  //   }
  //   fscanf(file, "%c", &read_char);
  //   table[read_char] += 1;
  // }
  // fclose(file);

  FILE * bruno = fopen("saida.pdf","wb");

  while(fread(&read_char, sizeof(unsigned char), 1, file)){
    table[read_char] += 1;

    fwrite(&read_char,sizeof(unsigned char),1,bruno);
    printf("caracter lido => %c\n", read_char);
  } 
  fclose(file);

  fclose(bruno);

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
unsigned char **CreateEncodeTable(List *list)
{
  Tree *tree = GetTree(list);

  unsigned char **table = malloc(sizeof(unsigned char *) * SIZE);
  // A tabela possuirá uma coluna a mais que a altura da árvore, pois deve comportar o '\0' das strings
  for (int x = 0; x < SIZE; x++)
  {
    table[x] = calloc(TreeHeight(tree) + 1, sizeof(unsigned char));
  }

  FillEncodeTable(table, tree, "", TreeHeight(tree));
  return table;
}

//=======================================================================//
void PrintEncodeTable(unsigned char **table)
{
  printf("Tabela de codificacao======\n\n");
  for (int x = 0; x < SIZE; x++)
  {
    printf("%d -> %s\n", x, table[x]);
  }
}

//=======================================================================//
void DestructEncodeTable(unsigned char ** table){
  if(table){
    for(int x=0; x<SIZE;x++){
      if(table[x]) free(table[x]);
    }
    free(table);
  }
}

//=======================================================================//
unsigned char *ReadFile(unsigned char *fileWay, unsigned char ** table, long int fileSize)
{
  FILE *file = fopen(fileWay, "rb");
  long int tam;

  // aponta para o final do arquivo
  fseek(file, 0, SEEK_END);
  // Conta a quantidade de bytes que o arquivo possui do ínicio até a posição atual
  tam = ftell(file);
  printf("tamanho do arquivo = %ld\n", tam);

  unsigned char *text = calloc(tam, sizeof(unsigned char));
  // voltando o ponteiro para o inicio do arquivo
  fseek(file, 0, SEEK_SET);
  
  // fscanf(file, "%[^EOF]", text);
  //MODIFICADO
  // fread(text,sizeof(unsigned char),tam,file);
  // printf("texto => %s\n", text);

  FILE * jaozim = fopen("coroepancada.pdf","wb");

  long int counter=0;
  unsigned char byte;
  while(fread(&byte,sizeof(unsigned char),1, file)){
    text[counter] = byte;
    counter++;
  }
    fwrite(text,sizeof(unsigned char),tam,jaozim);

    long int asd= strlen(text);
    printf("tamain = %ld\n", asd);

    printf("contador = %ld\n",counter);
  // printf("texto => %s\n", text);

  fclose(jaozim);
  fclose(file);

  return text;
}

//=======================================================================//
unsigned char *EncodeText(unsigned char **encodeTable, unsigned char *text, long int fileSize, long int * encodedTextSize)
{

  printf("fileSize encode = %ld\n", fileSize);


  long int size = 0;

  for (int x = 0; x<fileSize; x++)
  {
    // printf("caractere = %c\n", text[x]);
    size += strlen(encodeTable[text[x]]);
    // printf("code = %s\n",encodeTable[text[x]]);
  }

  *encodedTextSize = size;

  unsigned char *code = calloc(size, sizeof(unsigned char));
  for (int x = 0; x<fileSize; x++)
  {
    strcat(code, encodeTable[text[x]]);
  }

  return code;
}

//=======================================================================//
void CreateCompressedFile(unsigned char *text, unsigned char *name, int *frequencyTable, long int fileSize, long int encodedTextSize)
{
  unsigned char fileName[50], noEx[45], ext[5];
  sscanf(name, "%[^.]%s", noEx, ext);
  sprintf(fileName, "%s.comp", noEx);

  //DEPURAR
  printf("Nome da extensao = %s\n", ext);

  FILE *file = fopen(fileName, "wb");
  if (!file)
  {
    printf("File creation failed!\n");
    exit(1);
  }

  // Procurar um jeito de escrever a arvore ou a tabela de codificação no arquivo
  fwrite(frequencyTable, sizeof(int), 256, file);

  //MODIFICADO
  fwrite(ext,sizeof(unsigned char),5,file);

  unsigned long int encodedTextLenght = encodedTextSize;

  printf("encoded text size = %ld\n", encodedTextSize);

  fwrite(&encodedTextLenght, sizeof(unsigned long int),1,file);

  unsigned char binary = 0;
  unsigned char aux = 1;

  for (int x = 0, y = 7; x<encodedTextSize; x++, y--)
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
void UnzipFile(FILE *compressedFile, List *list, unsigned char *fileName)
{ 
  unsigned char name[50], noEx[45];
  sscanf(fileName, "%[^.]", noEx);
  

  Tree *tree = GetTree(list);
  unsigned char binary;
  unsigned char aux = 1;

  //MODIFICADO
  unsigned char ext[5];
  fread(ext,sizeof(unsigned char),5,compressedFile);
  //DEPURAR
  printf("Nome da extensao depois de descompactar = %s\n", ext);

  //Colocando o nome da extensão no arquivo
  sprintf(name, "%s%s", noEx,ext);
  //Abrindo arquivo descompactado
  FILE *unzipedFile = fopen(name, "wb");


  unsigned long int encodedTextLenght=0;
  fread(&encodedTextLenght, sizeof(unsigned long int), 1, compressedFile);

  unsigned long int byteCounter=0;
  unsigned char writeChar = '\0';

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
        // fprintf(unzipedFile, "%c", GetTreeChar(tree));
        writeChar = GetTreeChar(tree);
        printf("caracter lido = %c\n", writeChar);
        fwrite(&writeChar,sizeof(unsigned char),1,unzipedFile);
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
  fclose(unzipedFile);
}