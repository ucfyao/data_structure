#include<stdlib.h>  
#include<stdio.h> 
// 初始化参数
#define MAX 20  
#define LISTINCREMENT 10 

#define OVERFLOW -2

#define TRUE 1
#define FALSE 0

typedef struct {
    int *elem;
    int length;
    int listsize;

} SqList;

// 初始化线性表
int initSqList(SqList *L){
    // 开辟空间，将地址赋予指针
    L->elem = (int *) malloc(MAX * sizeof(int));
    if(!L->elem) exit(OVERFLOW) ;
    L->listsize = MAX;
    printf("输入表的长度：");  
    scanf("%d",&L->length);  
    printf("输入%d个数：",L->length);  
    for(int i=0;i<L->length;i++){
        scanf("%d",&L->elem[i]);
    }
    return TRUE;
}
// 列表
int traverse(SqList *L){
    //遍历  
    printf("表中数据为："); 
    for(int i=0; i < L->length;i++){
        printf("%3d",L->elem[i]);
    }
    printf("\n");  
    return TRUE;
}
// 插入
int insert(SqList *L){
    // 插入元素及其要插入的位置 
    int i;
    int e;
    printf("输入要插入的位置及元素\n");
    scanf("%d%d",&i,&e);
    printf("在顺序线性表中第%d个位置之前插入新的元素%d。\n",i,e);
    if(i > L->length+1 || i<1) return FALSE;
    int *p,*q;
    q = &(L->elem[i-1]);
    p = &(L->elem[L->length-1]);
    for(p ; p >= q; --p) {
        *(p+1) = *p;
    }
    *q = e;
    ++L->length;
    return TRUE;

}
// 删除
int delete(SqList *L){
     // 删除元素位置或根据元素查询位置
    int i,e;
    printf("输入要删除第几个元素");
    scanf("%d",&i);
    if((i < 1) || (i > L->length)) return FALSE;
    int *p,*q;
    p = &(L->elem[i-1]);
    e = *p;
    q = L->elem + L->length-1;
    for(++p; p<=q; ++p) {
        // 被删除元素之后的元素左移
        *(p-1) = *p;
    }
    --L->length;
    printf("元素被删除");
    return TRUE;
}
// 查找
int find(SqList *L){
    printf("输入查找的元素："); 
    int e; 
    scanf("%d",&e);
    for(int i = 0; i < L->length; i++)
    {
        if(L->elem[i] == e){
            printf("查找成功，查找元素为%d \n",L->elem[i]);  
            return TRUE;
        }
    }
    printf("查找失败 \n");  
    return FALSE;
}


int main(){
    SqList L;
    initSqList(&L);
    traverse(&L);
    find(&L);
    insert(&L);
    traverse(&L);
    delete(&L);
    traverse(&L);
    return 0;  
}  