#ifndef tree_h
#define tree_h

//Tipo árvore (tipo incompleto - só é possível manipulá-lo através de suas funções)
typedef struct tree Tree;

/*Cria uma árvore vazia
*inputs: nenhum
*output: ponteiro para a árvore vazia
*pre-condição: nenhuma 
*pós-condição: existe uma árvore que aponta para NULL
*/
Tree *CreateVoidTree();

/*Cria um nó folha
*inputs: sub-árvore da direita, sub-árvore da esquerda, o peso do nó(frequência do byte no arquivo)
e o caracter do nó
*output: ponteiro para o nó folha criado
*pré-condição: 2 sub-árvores vazias(NULL), o peso e o caracter existem
*pós-condição: existe um novo nó alocado dinamicamente
*/
Tree *CreateLeafNode(Tree *left, Tree *right, int weight, unsigned char character);

/*Cria um nó interno
*inputs: sub-árvore da direita, sub-árvore da esquerda e o peso
do nó(soma dos pesos dos nós que originaram as sub-árvores)
*output: ponteiro para o nó interno criado
*pré-condição: duas árvores não nulas e o peso do nó existem
*pós-condição: existe um novo nó alocado dinamicamente
*/
Tree *CreateInternalNode(Tree *left, Tree *right, int weight);

/*Retorna a altura da árvore
*inputs: ponteiro para o nó raíz 
*output: um 'int' indicando a altura da árvore
*pré-condição: existe uma árvore
*pós-condição: a árvore não é modificada
*/
int TreeHeight(Tree *tree);

/*Peso de um nó
*inputs: ponteiro para o nó que deseja analisar
*output: um 'int' com o peso do nó
*pré-condição: existe um nó
*pós-condição: o nó não é modificado
*/
int TreeWeight(Tree *tree);

/*Imprime a árvore
*inputs: ponteiro para a árvore que deseja imprimir
*output: nenhum
*pré-condição: árvore existe
*pós-condição: nenhuma
*/
void PrintTree(Tree * tree);

/*Retorna a sub-árvore da esquerda
*inputs: ponteiro para a árvore que deseja analisar
*output: ponteiro para a sub-árvore da esquerda
*pré-condição: árvore existe
*pós-condição: árvore não é modificada
*/
Tree * GetLeftTree(Tree * tree);

/*Retorna a sub-árvore da direita
*inputs: ponteiro para a árvore que deseja analisar
*output: ponteiro para a sub-árvore da direita
*pré-condição: árvore existe
*pós-condição: árvore não é modificada
*/
Tree * GetRightTree(Tree * tree);

/*Retorna o caracter do nó
*inputs: o nó que deseja analisar
*output: o caracter do nó
*pré-condição: existe o nó
*pós-condição: o nó não é modificado
*/
unsigned char GetTreeChar(Tree * tree);

/*Libera memória alocada para a árvore
*inputs: árvore a ser liberada
*output: nenhum
*pré-condição: árvore existe
*pós-condição: memória alocada para árvore está livre
*/
void DestructTree(Tree * tree);

#endif // !tree_h

/*OBS: Sabemos que as funções CreateLeafNode e CreateInternalNode diferem apenas no caracter inserido,
*porém optamos por fazer duas funções a fim de obter melhor legibilidade e compreensão do código.
*/