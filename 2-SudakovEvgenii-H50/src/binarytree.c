
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "binarytree.h"



binaryTree*  BinaryTreeInsertNode(int data, binaryTree* tree){
    if(tree == NULL){
        tree = (binaryTree*)malloc(sizeof(binaryTree));
        if(tree == NULL){
            return NULL;
        }
        tree->key = data;
        tree->left = NULL;
        tree->right = NULL;
    }
    else if(data < tree->key){
        tree->left = BinaryTreeInsertNode(data,tree->left);
    }
    else if(data > tree->key){
        tree->right = BinaryTreeInsertNode(data, tree->right);
    }
    return tree;

}


int BinaryTreeSearch(binaryTree * tree, int find) {
    int isInTree = 0;
    if ( tree == NULL) {
        return isInTree;
    }
    if (find < tree->key) {
        isInTree = BinaryTreeSearch(tree->left, find);
    }
    else if (find > tree->key) {
        isInTree = BinaryTreeSearch(tree->right, find);
    }
    else {
        isInTree = 1;
    }
    return isInTree;
}

binaryTree* Del1(binaryTree** q, binaryTree* p){
    binaryTree* r;
    if ((*q)->right){
        r = Del1(&(*q)->right, p);
    }
    else{
        p->key = (*q)->key;
        r = *q;
        *q = (*q)->left;
    }
    return r;
}





binaryTree* BinaryTreeDeleteNode(int data, binaryTree* tree){
    binaryTree * p;
    if( tree != NULL) {
        if(data < tree -> key){
            tree->left = BinaryTreeDeleteNode(data, tree->left);
        }
        else if( data > tree->key){
            tree->right= BinaryTreeDeleteNode(data, tree->right);
        }
        else{
            p = tree;
            if (!p->right){
                tree = p->left;
            }
            else{
                if (!p->left){
                    tree = p->right;
                }
                else{
                    p = Del1(&p->left, p);

                }

                free(p);
            }
        }
    }
    return tree;
}



void BinaryTreePrint(binaryTree* tree){
    if(tree == NULL){
        return;
    }
    printf("%d ",tree->key);
    BinaryTreePrint(tree->left);
    BinaryTreePrint(tree->right);
}





void BinaryTreeDestroy(binaryTree* tree){
    if(tree == NULL){
        return;
    }
    BinaryTreeDestroy(tree->left);
    BinaryTreeDestroy(tree->right);
    free(tree);

}



