#ifndef tree_h
#define tree_h

typedef struct tree Tree;

Tree *CreateVoidTree();

Tree *CreateLeafNode(Tree *left, Tree *right, int weight, char character);

Tree *CreateInternalNode(Tree *left, Tree *right, int weight);

int TreeHeight(Tree *tree);

int TreeWeight(Tree *tree);

#endif // !tree_h
