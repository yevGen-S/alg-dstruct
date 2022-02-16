typedef struct binaryTree {
    int key;
    struct binaryTree *left;
    struct binaryTree *right;
}binaryTree;



binaryTree*  BinaryTreeInsertNode(int data, binaryTree* tree);
binaryTree* BinaryTreeDeleteNode(int data, binaryTree* tree);
void BinaryTreePrint(binaryTree* tree);
int BinaryTreeSearch(binaryTree * tree, int find) ;
void BinaryTreeDestroy(binaryTree* tree);
