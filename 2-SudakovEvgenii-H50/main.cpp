#include <stdio.h>
#include <stdlib.h>


typedef  struct AATree{
    struct AATree* left;
    struct AATree* right;
    int level;
    int key;
}AATree;


void AATreeInit(void);
AATree* AATreeScew(AATree* tree);
AATree* AATreeSplit(AATree* tree);
AATree*  AATreeInsertNode(int data, AATree* tree);
AATree* AATreeDeleteNode(int data, AATree* tree);
void AATreePrint(AATree* t, int y);
int AATreeSearch(AATree * tree, int find) ;
void AATreeDestroy(AATree* tree);
void AATreePrint2(AATree* tree);


static AATree* bottom = NULL;
static AATree* deleted = NULL;
static AATree* last = NULL;
static int x = 1;



//void gotoxy( int y){
//    COORD c = { (short)x, (short)y };
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
//}


//void AATreePrint(AATree* t, int y){
//    if (t != bottom){
//        AATreePrint(t->left ,y + 2);
//        gotoxy(y);
//        printf("%d ", t->key);
//        x += 7;
//        AATreePrint(t->right,y + 2);
//    }
//}



void AATreeInit(void){
    if( bottom == NULL) {
        bottom = (AATree *) malloc(sizeof(AATree));
        if (bottom != NULL) {
            bottom->level = 0;
            bottom->left = bottom;
            bottom->right = bottom;
            deleted = bottom;
        }
    }

}


AATree* AATreeScew(AATree* tree){
    AATree* temp;
    if(tree->left->level == tree->level){ // left horizontal edge
        //rotate right
        temp = tree;
        tree = tree->left;
        temp->left = tree->right;
        tree->right = temp;
    }
    return tree;
}


AATree* AATreeSplit(AATree* tree){
    AATree * temp;
    if(tree->right->right->level == tree->level){ //two right horizontal edges
        //rotate left
        temp = tree;
        tree = tree->right;
        temp->right = tree->left;
        tree->left = temp;
        tree->level = tree->level + 1;
    }
    return tree;
}


AATree* AATreeInsertNode(int data, AATree* tree){
    if( tree == bottom || tree == NULL){
        tree = (AATree*)malloc(sizeof(AATree));
        if(tree == NULL)
            return NULL;
        else {
            tree->key = data;
            tree->left = bottom;
            tree->right = bottom;
            tree->level = 1;
        }
    }
    if( data < tree->key ){
        tree->left = AATreeInsertNode(data, tree->left);
    }
    else if( data > tree->key ){
        tree->right = AATreeInsertNode(data, tree->right);
    }
    tree = AATreeScew(tree);
    tree = AATreeSplit(tree);
    return tree;
}


AATree* AATreeDeleteNode(int data, AATree* tree){
    if (tree != bottom && tree!= NULL) {
        last = tree;
        if (data < tree->key) {
            tree->left = AATreeDeleteNode(data, tree->left);
        }
        else {
            deleted = tree;
            tree->right = AATreeDeleteNode(data, tree->right);
        }

        if (tree == last && deleted != bottom && data == deleted->key) {
            deleted->key = tree->key;
            deleted = bottom;
            tree = tree->right;
            free(last);

        }
        else if ((tree->left->level < tree->level - 1 )|| (tree->right->level < tree->level - 1)) {
            tree->level = tree->level - 1;

            if (tree->right->level > tree->level) {
                tree->right->level = tree->level;
            }

            tree = AATreeScew(tree);
            tree->right = AATreeScew(tree->right);
            tree->right->right = AATreeScew(tree->right->right);
            tree = AATreeSplit(tree);
            tree->right = AATreeSplit(tree->right);
        }
    }
    return tree;
}


int AATreeSearch(AATree * tree, int find) {
    int isInTree = 0;
    if (tree == bottom || tree == NULL) {
        return isInTree;
    }
    if (find < tree->key) {
        isInTree = AATreeSearch(tree->left, find);
    }
    else if (find > tree->key) {
        isInTree = AATreeSearch(tree->right, find);
    }
    else {
        isInTree = 1;
    }
    return isInTree;
}


void AATreePrint2(AATree* tree){
    if( tree == bottom || tree == NULL){
        return;
    }
    printf("%d ",tree->key);
    AATreePrint2(tree->left);
    AATreePrint2(tree->right);

}



void AATreeDestroy(AATree* tree) {
    if (tree == bottom || tree == NULL) {
        return;
    }
    AATreeDestroy(tree->left);
    AATreeDestroy(tree->right);
    free(tree);
}







int main(void) {
    char command;
    int key;
    int y = 1;
    AATree *t = NULL;
    AATreeInit();
    while (scanf("%c", &command) >= 1) {
        if (command != 'p' && command != 'q')
            scanf("%i", &key);
        switch (command) {
            case 'a':
                t = AATreeInsertNode(key, t);
                break;
            case 'r':
                t = AATreeDeleteNode(key, t);
                break;
            case 'f':
                if (AATreeSearch(t, key))
                    puts("yes");
                else
                    puts("no");
                break;
            case 'p':
                AATreePrint2(t);
                putchar('\n');
                break;
            case 'q':
                AATreeDestroy(t);
                return 0;
        }
    }

}
