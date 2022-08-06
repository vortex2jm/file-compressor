#include "table.h"
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=======================================================================//
int *CreateFrequencyTable(char *fileWay) {

  static int table[SIZE] = {0};
  unsigned char read_char = '\0';
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

//=======================================================================//
void PrintFrequencyTable(int * table){

  printf("\n====Tabela de frequencia====\n\n");

  for(int x=0;x<SIZE;x++){
    if(table[x]){
      printf("%d -> %d\n", x, table[x]);
    }
  }
}

//=======================================================================//
char ** CreateEncodeTable(List * list){

  Tree * tree = GetTree(list);

  char ** table = malloc(sizeof(char*)*SIZE);
  //A tabela possuirá uma coluna a mais que a altura da árvore, pois deve comportar o '\0' das strings
  for(int x=0;x<SIZE;x++){
    table[x] = calloc(TreeHeight(tree)+1, sizeof(char));
  }

  FillEncodeTable(table, tree,"",TreeHeight(tree));
  return table;
} 

//=======================================================================//
void PrintEncodeTable(char ** table){
  printf("Tabela de codificacao======\n\n");
  for(int x=0;x<SIZE;x++){
    printf("%d -> %s\n", x, table[x]);
  }  
}

//=======================================================================//
char * ReadFile(char * fileWay){

  FILE * file = fopen(fileWay,"r");
  long int tam;

  //aponta para o final do arquivo
  fseek(file, 0, SEEK_END);
  //Conta a quantidade de bytes que o arquivo possui do ínicio até a posição atual
  tam = ftell(file);
  // printf("Tamanho do arquivo = %ld\n", tam);


  char * text = calloc(tam, sizeof(char));
  //voltando o ponteiro para o inicio do arquivo
  fseek(file,0,SEEK_SET);
  fscanf(file,"%[^EOF]",text);

  return text;
}

//=======================================================================//
char * EncodeText(char ** encodeTable, char * text){

  long int size=1;
  for(int x=0; text[x]!='\0'; x++){
    size += strlen(encodeTable[text[x]]);
  } 

  char * code = calloc(size,sizeof(char));
  for(int x=0; text[x]!='\0';x++){
    strcat(code, encodeTable[text[x]]);
  }
  return code;
}

//=======================================================================//
void CompressText(unsigned char * text, char * name){

  char fileName[50], noEx[45];
  sscanf(name, "%[^.]",noEx);
  sprintf(fileName,"%s.comp",noEx);

  FILE * file = fopen(fileName, "wb");
  if(!file){
    printf("File creation failed!\n");
    exit(1);
  }

  unsigned char binary = 0;
  unsigned char aux = 1;

  for(int x=0, y=7; text[x]!='\0';x++,y--){
    aux = 1;
    if(text[x] == '1'){
      aux = aux << y;
      binary = binary | aux;
    }
    if(y<0){
      fwrite(&binary, sizeof(unsigned char),1, file);  
      y=7;
      binary = 0;
    }
  }
  if(strlen(text)%8)(&binary, sizeof(unsigned char),1, file);
  fclose(file);
}
