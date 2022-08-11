#ifndef list_h
#define list_h
#include "binary_tree.h"

//Tipo lista de árvores(tipo incompleto - só é possível manipulá-lo através de suas funções)
typedef struct list List;

/*Cria uma lista vazia
inputs: nenhum
output: ponteiro para uma lista vazia
pré-condição: nenhuma
pós-condição: existe uma nova lista 
*/
List *CreateVoidList();

/*Insere na lista de forma ordenada
inputs: a lista e a árvore que deseja inserir
output: ponteiro para a lista
pré-condição: a lista e a aŕvore existem
pós-condição: a lista é acrescida de uma árvore
*/
List *ListPush(List *list, Tree *tree);

/*Imprime a lista
inputs: lista a ser imprimida
output: nenhum
pré-condição: a lista existe
pós-condição: nenhuma
*/
void PrintList(List *list);

/*Libera a memória alocada para a lista
inputs: lista a ser liberada
output: nenhum
pré-condição: a lista existe
pós-condição: memória alocada pela lista está liberada
*/
void DestructList(List *list);

/*Cria uma lista com nós folhas do tipo Tree a partir de uma tabela de frequência
inputs: a tabela de frequência
output: ponteiro para a lista criada
pré-condição: a tabela de frequência existe
pós-condição: existe uma nova lista
*/
List * CreateHuffmanList(int * frequencyTable);

/*Executa o algoritmo de Huffman em uma lista de árvores
inputs: ponteiro para a lista de árvores a ser modificada
output: ponteiro para a lista de árvores modificada
pré-condição: a lista existes
pós-condição: lista modificada; agora existe apenas uma árvore na lista
*/
List * Huffman_Execute(List * list);

/*Retorna a primeira árvore da lista
inputs: ponteiro para a lista
output: ponteiro para a primeira árvore da lista
pré-condição: a lista existe
pós-condição: a lista não é modificada
*/
Tree * GetTree(List * list);

#endif // !list_h
