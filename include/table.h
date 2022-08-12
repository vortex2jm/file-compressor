#ifndef file_manager_h
#define file_manager_h
#include "ordered_list.h"
#include <stdio.h>
#define SIZE 256

/*Cria uma tabela de frequência de bytes em um arquivo binário
inputs: uma string com o caminho do arquivo
output: ponteiro para a tabela 
pré-condição: existe um arquivo binário
pós-condição: existe um vetor com as frequências dos bytes do arquivo
*/
int *CreateFrequencyTable(unsigned char *fileWay);

/*Imprime uma tabela de frequência
inputs: ponteiro para a tabela
output: nenhum
pré-condição: existe a tabela
pós-condição: nenhuma
*/
void PrintFrequencyTable(int * table);

/*Cria um dicionário de codificação para os caracteres presente na primeira
árvore da lista
inputs: ponteiro para a lista 
output: uma matriz(tabela) com o código de cada caracter
pré-condição: existe uma lista com apenas uma árvore(ótima)
pós-condição: a lista não é modificada, existe uma tabela de codificação
*/
unsigned char ** CreateEncodeTable(List * list);

/*Imprime a tabela de codificação
inputs: ponteiro para a tabela
output: nenhum
pré-condição: existe a tabela
pós-condição: nenhuma
*/
void PrintEncodeTable(unsigned char ** table);

/*Libera memória alocada para uma tabela de codificação
inputs: ponteiro para a tabela
output: nenhum
pré-condição: existe uma tabela
pós-condição: a memória alocada para a tabela está livre
*/
void DestructEncodeTable(unsigned char ** table);

/*Lê um arquivo binário byte a byte
inputs: o caminho do arquivo e o tamanho do arquivo em bytes
output: ponteiro para uma stream com todos os bytes do arquivo
pré-condição: existe um arquivo binário e seu tamanho já foi lido
pós-condição: o arquvio não é modificado, existe um vetor com os bytes do arquivo
*/
unsigned char * ReadFile(unsigned char * fileWay, long int fileSize);

/*Codifica uma sequência de bytes com base em uma tabela de codificação
inputs: a tabela de codificação, a stream a ser codificada, seu tamanho e um ponteiro 
para uma variável que comportará o tamanho da stream codificada 
output: ponteiro para a stream codificada
pré-condição: existe a tabela de codificação, existe uma stream a ser codificada, 
o tamanho dessa stream já foi lido, existe uma variável declarada para receber o tamanho da stream codificada
pós-condição: existe um vetor com uma sequência de bytes codificada 
*/
unsigned char * EncodeText(unsigned char ** encodeTable, unsigned char * text, long int fileSize, long int * encodedTextSize);

/*Preenche a tabela de codificação
inputs: ponteiro para um espaço de memória alocado para a tabela, árvore criada pelo algoritmo 
de Huffman, uma string(vazia) e a altura da árvore  
output: nenhum
pré-condição: existe uma matriz alocada para a tabela de codificação, existe uma árvore ótima
criada pelo algoritmo de Huffman, existe uma string vazia na qual será preenchida com o código
de cada byte, altura da árvore lida
pós-condição: matriz preenchida com a tabela de codificação
*/
void FillEncodeTable(unsigned char **table, Tree *tree, unsigned char *code, int treeHeight);

/*Cria arquivo comprimido
inputs: stream codificada, nome do arquivo a ser comprimido, tabela de frequência de seus bytes
e tamanho da stream codificada
output: nenhum
pré-condição: existe um arquivo binário, a sequência de bytes do arquivo já foi codificada de acordo
com a árvore de Huffman, a tabela de frequência de seus bytes já foi criada e o tamanho da stream 
codificada já foi lido 
pós-condição: é criado um arquivo compactado com a extensão '.comp'
*/
void CreateCompressedFile(unsigned char * text, unsigned char * name, int * frequencyTable, long int encodedTextSize);

/*Descomprime o arquivo
inputs: ponteiro para o arquivo, uma lista de árvores, nome do arquivo
output: nenhum
pré-condição: o arquivo existe e já foi aberto, a lista de árvores já foi lida de seu cabeçalho
pós-condição: O arquivo no qual originou o arquivo compactado é recriado
*/
void UnzipFile(FILE *compressedFile, List *list, unsigned char *fileName);

/*Retorna o tamanho de um arquivo binário
inputs: nome do arquivo
output: um 'long int' com o tamanho do arquivo em bytes
pré-condição: o arquivo existe 
pós-condição: o arquivo não é modificado
*/
long int GetFileSize(char * fileName);

#endif // !file_manager_h