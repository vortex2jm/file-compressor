#ifndef tree_h
#define tree_h

typedef struct tree Tree;

Tree *CreateVoidTree();

Tree *CreateLeafNode(Tree *left, Tree *right, int weight, unsigned char character);

Tree *CreateInternalNode(Tree *left, Tree *right, int weight);

int TreeHeight(Tree *tree);

int TreeWeight(Tree *tree);

void PrintTree(Tree * tree);

Tree * GetLeftTree(Tree * tree);

Tree * GetRightTree(Tree * tree);

unsigned char GetTreeChar(Tree * tree);

void DestructTree(Tree * tree);

void FillEncodeTable(char ** table, Tree * tree, unsigned char * code, int treeHeight);

#endif // !tree_h
