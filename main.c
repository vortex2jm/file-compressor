#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "ordered_list.h"

int main(){

    List *list = CreateVoidList();  
    
    Tree *tree1, *tree2, *tree3, *tree4, *tree5;

    tree1 = CreateInternalNode(CreateVoidTree(), CreateVoidTree(), 1);
    tree2 = CreateInternalNode(CreateVoidTree(), CreateVoidTree(), 1);
    tree3 = CreateInternalNode(CreateVoidTree(), CreateVoidTree(), 2);
    tree4 = CreateInternalNode(CreateVoidTree(), CreateVoidTree(), 3);
    tree5 = CreateInternalNode(CreateVoidTree(), CreateVoidTree(), 0);

    ListPush(list, tree1);
    ListPush(list, tree2);
    ListPush(list, tree3);
    ListPush(list, tree4);
    ListPush(list, tree5);

    PrintList(list);

    return 0;
}