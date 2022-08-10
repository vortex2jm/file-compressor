#include "../include/binary_tree.h"
#include "../include/ordered_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree
{
  int weight;
  unsigned char character;
  Tree *left;
  Tree *right;
};

//=======================================================================//
Tree *CreateVoidTree() { return NULL; }

//=======================================================================//
Tree *CreateLeafNode(Tree *left, Tree *right, int weight, unsigned char character)
{
  Tree *tree = malloc(sizeof(Tree));
  tree->left = left;
  tree->right = right;
  tree->weight = weight;
  tree->character = character;

  return tree;
}

//=======================================================================//
Tree *CreateInternalNode(Tree *left, Tree *right, int weight)
{
  Tree *tree = malloc(sizeof(Tree));
  tree->left = left;
  tree->right = right;
  tree->weight = weight;
  tree->character = '\0';

  return tree;
}

//=======================================================================//
int TreeHeight(Tree *tree)
{
  if (!tree)
    return -1;

  if (TreeHeight(tree->left) > TreeHeight(tree->right))
    return 1 + TreeHeight(tree->left);
  else
    return 1 + TreeHeight(tree->right);
}

//=======================================================================//
int TreeWeight(Tree *tree)
{
  if (!tree)
    return -1;
  return tree->weight;
}

//=======================================================================//
void PrintTree(Tree *tree)
{
  if (tree)
  {
    printf("-> %d / %c\n", tree->weight, tree->character);
    PrintTree(tree->left);
    PrintTree(tree->right);
  }
}

//=======================================================================//
Tree * GetLeftTree(Tree * tree){
  return tree->left;
}

//=======================================================================//
Tree * GetRightTree(Tree * tree){
  return tree->right;
}

//=======================================================================//
unsigned char GetTreeChar(Tree * tree){
  if(!tree) return '\0';
  return tree->character;
}

//=======================================================================//
void DestructTree(Tree * tree){
  if(tree){
    DestructTree(tree->left);
    DestructTree(tree->right);
    free(tree);
  }
}