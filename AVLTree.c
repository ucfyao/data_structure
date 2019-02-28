#include<stdio.h>
#include<stdlib.h>


typedef int Type;

typedef struct AVLTreeNode{
    // 关键字(键值)
    Type key;
    int height;
    // 左孩子
    struct AVLTreeNode *left;
    // 右孩子
    struct AVLTreeNode *right;
}Node, *AVLTree;

#define HEIGHT(p)    ( (p==NULL) ? -1 : (((Node *)(p))->height) )
#define MAX(a,b)    ( (a) > (b) ? (a) : (b) )

// 创建节点
static Node * initNode(Type key, Node *left,Node *right){
    Node * p;
    if((p = (Node *) malloc(sizeof(Node))) == NULL){
        return NULL;
    }
    p->key = key;
    p->height = 0;
    p->left = left;
    p->right = right;
    return p;
}

// 获取树的高度
int height(AVLTree tree){
    return (tree == NULL) ? -1 : ((Node *)(tree))->height;
}

// 前序遍历
void preOrder(AVLTree tree){
    if( tree != NULL){
        printf("%d", tree->key);
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

// 中序遍历
void inOrder(AVLTree tree){
    if( tree != NULL){
        inOrder(tree->left);
        printf("%d", tree->key);
        inOrder(tree->right);
    }
}

// 后序遍历
void postOrder(AVLTree tree){
    if( tree != NULL){
        postOrder(tree->left);
        postOrder(tree->right);
        printf("%d", tree->key);
    }
}

// 查找键值为key的节点(递归实现)
Node* search(AVLTree x, Type key){
    if( x == NULL || x->key == key){
        return x;
    }
    if( key < x->key){
        return search(x->left,key);
    }else{
        return search(x->right,key);
    }
}

// 查找键值为key的节点(非递归实现)
Node* iterativeSearch(AVLTree x, Type key){
    while((x != NULL) && (x->key !=key)){
        if(key < x->key){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    return x;
}

// 查找最小节点
Node * minimum(AVLTree tree){
    if(tree == NULL){
        return NULL;
    }
    while(tree->left != NULL){
        tree = tree->left;
    }
    return tree;
}


// 最大节点
Node * maximum(AVLTree tree){
    if(tree == NULL){
        return NULL;
    }
    while (tree->right != NULL){
        tree = tree->right;
    }
    return tree;
}

// 左左对应的情况。返回值：旋转后的根节点
static Node * left_left_rotation(AVLTree k2){
    AVLTree k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = MAX(HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
    k1->height = MAX( HEIGHT(k1->left), k2->height) + 1;
    return k1;
}

// RR：右右对应的情况(右单旋转)。返回值：旋转后的根节点
static Node* right_right_rotation(AVLTree k1){
    AVLTree k2;
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height =  MAX( HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
    k2->height = MAX( HEIGHT(k2->right), k1->height) + 1;
    
    return k2;

}
// LR：左右对应的情况(左双旋转)。返回值：旋转后的根节点
static Node* left_right_rotation(AVLTree k3){
     k3->left = right_right_rotation(k3->left);
     return left_left_rotation(k3);
}

// RL：右左对应的情况(右双旋转)。返回值：旋转后的根节点
static Node* right_left_rotation(AVLTree k1){
    k1->right = left_left_rotation(k1->right);
    return right_right_rotation(k1);
}

// 插入节点
Node* insert(AVLTree tree , Type key){
    if(tree == NULL){
        // 新建节点
        tree = initNode(key , NULL,NULL);
        if(tree == NULL){
            printf("ERROR: create avl tree node failed");
            return NULL;
        }
    }else if( key < tree->key){
        // 将key插入到左子树的情况
        tree->left = insert(tree->left, key);
        // 插入后，若avl失去平衡，则进行相应的调整
        if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2){
            if (key < tree->left->key){
                tree = left_left_rotation(tree);
            }else{
                tree = left_right_rotation(tree);
            }
        }
    }else if(key > tree->key){
        // 插入右子树的情况
        tree->right = insert(tree->right, key);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = right_right_rotation(tree);
            else
                tree = right_left_rotation(tree);
        }
    }else{
        //  添加相同数据的情况
        printf("添加失败：不允许添加相同的节点！\n");
    }
    tree->height = MAX( HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
    return tree;
}

// 删除结点(z)，返回根节点
static Node* del(AVLTree tree, Node *z){
    // 根为空 或者 没有要删除的节点，直接返回NULL。
    if (tree==NULL || z==NULL){
        return NULL;
    }
    // 待删除的节点在"tree的左子树"中
    if (z->key < tree->key){
        tree->left = del(tree->left, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2){
            Node *r =  tree->right;
            if (HEIGHT(r->left) > HEIGHT(r->right)){
                 tree = right_left_rotation(tree);
            }else{
                tree = right_right_rotation(tree);
            }
        }
    }else if(z->key > tree->key){
        // 待删除的节点在"tree的右子树"中
        tree->right = del(tree->right, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2){
            Node *l =  tree->left;
            if (HEIGHT(l->right) > HEIGHT(l->left)){
                tree = left_right_rotation(tree);
            }else{
                tree = left_left_rotation(tree);
            }
        }
    } else {
        // tree是对应要删除的节点。
        // tree的左右孩子都非空
        if ((tree->left) && (tree->right)){
            if (HEIGHT(tree->left) > HEIGHT(tree->right)){
                // 如果tree的左子树比右子树高；
                // 则(01)找出tree的左子树中的最大节点
                //   (02)将该最大节点的值赋值给tree。
                //   (03)删除该最大节点。
                // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。

                Node *max = maximum(tree->left);
                tree->key = max->key;
                tree->left = del(tree->left, max);
            }else{
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给tree。
                //   (03)删除该最小节点。
                // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。

                 Node *min = maximum(tree->right);
                 tree->key = min->key;
                 tree->right = del(tree->right, min);
            }
        }else{
            Node *tmp = tree;
            tree = tree->left ? tree->left : tree->right;
            free(tmp);
        }
    }
    return tree;
}

// 删除结点(key是节点值)，返回根节点
Node* avltreeDel(AVLTree tree, Type key){
    Node *z;
    if ((z = search(tree, key)) != NULL)
    {
        tree = del(tree, z);
    }
    return tree;
}

// 销毁AVL树
void destroy(AVLTree tree){
    if (tree==NULL){
        return ;
    }
    if (tree->left != NULL){
        destroy(tree->left);
    }
    if (tree->right != NULL){
        destroy(tree->right);
    }
    free(tree);
}

// 打印"AVL树"
void printAvltree(AVLTree tree, Type key, int direction){
    if(tree != NULL){
        // tree是根节点
        if(direction==0){
            printf("%2d is root\n", tree->key, key);
        }else{
            printf("%2d is %2d's %6s child\n", tree->key, key, direction==1?"right" : "left");
        }
        printAvltree(tree->left, tree->key, -1);
        printAvltree(tree->right, tree->key, -1);
    }
}

int main(){

    static int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
    #define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )
    int i,ilen;
    AVLTree root = NULL;
    printf("== 高度: %d\n", height(root));
    printf("== 依次添加: ");
    ilen = TBL_SIZE(arr);
    for(i=0; i<ilen; i++){
        printf("%d ", arr[i]);
        root = insert(root, arr[i]);
    }

    printf("\n== 前序遍历: ");
    preOrder(root);

    printf("\n== 中序遍历: ");
    inOrder(root);

    printf("\n== 后序遍历: ");
    postOrder(root);

    printf("\n");

    printf("== 高度: %d\n", height(root));
    printf("== 最小值: %d\n", minimum(root)->key);
    printf("== 最大值: %d\n", maximum(root)->key);
    printf("== 树的详细信息: \n");
    printAvltree(root, root->key, 0);

    i = 8;
    printf("\n== 删除根节点: %d", i);
    root = avltreeDel(root, i);

    printf("\n== 高度: %d", height(root));
    printf("\n== 中序遍历: ");
    inOrder(root);
    printf("\n== 树的详细信息: \n");
    printAvltree(root, root->key, 0);

    // 销毁二叉树
    destroy(root);
}
