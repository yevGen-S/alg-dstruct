#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int key;
    int diff_height;
    struct tree* left;
    struct tree* right;
} tree;

tree * Insert(tree* t, int val);
void Insert_iterative(tree* t, int val);
tree* Del1(tree** q, tree* p);
tree* Del(tree* t, int val);
char Search(tree * t, int val);
int CountH(tree* node);
int GetHeightDiff(tree* t);
void PrintTree(tree* t, int y);
void DestroyTree(tree* t);


int x = 1;
tree * Insert(tree* t, int val){
    if (t == NULL){
        t = (tree*)malloc(sizeof(tree));
        t->key = val;
        t->left = t->right = NULL;
        t->diff_height = 0;
    }
    else{
        if (val < t->key){
            t->left = Insert(t->left, val);
            t->diff_height = GetHeightDiff(t);
        }
        else{
            if (val > t->key){
                t->right = Insert(t->right, val);
                t->diff_height = GetHeightDiff(t);

            }
        }
    }
    return t;
}


tree* Del1(tree** q, tree* p){
    tree* r;
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

tree* Del(tree* t, int val){
    tree* p;

    if (t){
        if (val < t->key){
            t->left = Del(t->left, val);
            t->diff_height = GetHeightDiff(t);
        }
        else{
            if (val > t->key){
                t->right = Del(t->right, val);
                t->diff_height = GetHeightDiff(t);
            }
            else{
                p = t;
                if (!p->right){
                    t = p->left;
                }
                else{
                    if (!p->left){
                        t = p->right;
                    }
                    else{
                        p = Del1(&p->left, p);
                        p->diff_height = GetHeightDiff(p);
                    }

                    free(p);
                }
            }
        }
    }
    return t;
}

//char Search(tree * t, int val){
//    if (!t)
//        return 0;
//    else {
//        if (val == t->key)
//            return 1;
//        else if (val > t->key)
//            Search(t->right, val);
//        else
//            Search(t->left, val);
//    }
//}


char Search_iterative(tree* t, int val){
    tree* node = t;
    while(node) {
        if (val == node->key)
            return 1;
        else if (val > node->key)
            node = node->right;
        else
            node = node->left;
    }
    return 0;
}

int CountH(tree* node){
    int l = 0, r = 0, h = 0;

    if (node == NULL)
        return 0;
    else{
        if (!node->left && !node->right)
            return 1;
        else{
            l = CountH(node->left);
            r = CountH(node->right);
            if (r > l)
                h = r + 1;
            else
                h = l + 1;
            return h;
        }
    }
}

int GetHeightDiff(tree* t){
    return abs(CountH(t->left) - CountH(t->right));
}

//void gotoxy( int y){
//    COORD c = { (short)x, (short)y };
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
//}

void PrintTree(tree* t, int y){
    if (t != NULL){
        PrintTree(t->left ,y + 2);
//        gotoxy(y);
        printf("%d(%d) ", t->key, t->diff_height);
//        x += 7;
        PrintTree(t->right,y + 2);

    }
}

void DestroyTree(tree* t){
    if (t){
        DestroyTree(t->left);
        DestroyTree(t->right);
        free(t);
    }
}

int main(){
    char command;
    int key;
    int y =1;
    tree* t = NULL;

    while (scanf("%c", &command) >= 1){
        if (command != 'p' && command != 'q')
            scanf("%i", &key);
        switch(command){
            case 'a':
                t= Insert(t, key);
                break;
            case 'r':
                t = Del(t, key);
                break;
            case 'f':
                if (Search_iterative(t, key))
                    puts("yes");
                else
                    puts("no");
                break;
            case 'p':
                PrintTree(t,y);
                break;
            case 'q':
                DestroyTree(t);
                return 0;

        }
    }

    return 0;
}