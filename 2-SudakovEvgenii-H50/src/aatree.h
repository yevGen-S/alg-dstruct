

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