#include "./include/binary_tree.h"
#include "./include/ordered_list.h"
#include "./include/table.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 
  //Salvando o tamanho do arquivo a ser compactado
  long int fileSize = GetFileSize(argv[1]);

  //Criando tabela de frequência
  int *frequencyTable = CreateFrequencyTable(argv[1]);

  //Criando a lista de árvores com os caracteres e suas frequências
  List *list = CreateHuffmanList(frequencyTable);

  //Executando o algoritmo de Huffman para obter uma árvore ótima
  Huffman_Execute(list);

  //Criando uma tabela com os códigos de todos os bytes presentes no arquivo
  unsigned char **table = CreateEncodeTable(list);

  //Lendo o arquivo e salvando seus bytes em um vetor
  unsigned char *text = ReadFile(argv[1],fileSize);
  
  //Declarando variável para salvar o tamanho do vetor que comportará a stream codificada
  long int encodedTextSize = 0;

  //Codificando o texto e salvando em um vetor
  unsigned char *encodedText = EncodeText(table, text, fileSize, &encodedTextSize);

  //Escrevendo o arquivo compactado
  CreateCompressedFile(encodedText, argv[1], frequencyTable, encodedTextSize);

  //Liberando a memória alocada
  DestructList(list);
  DestructEncodeTable(table);
  free(text);
  free(encodedText);

  return 0;
}