#include <stdio.h>
#include <stdlib.h>
#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define list_init_size 80 //初始分配存储空间
#define listincreament 10 //存储空间分配增量

//定义线性表的结构
typedef struct
{
    int *elem; // 存储空间地址
    int length; //当前长度
    int listsize; // 当前分配的存储容量
} SqList;

// 构造一个空的线性表（初始化）
int InitList_Sq(SqList *L)
{
    //动态开辟一维数组
    L->elem = (int *) malloc( list_init_size * sizeof(int) );
    //存储分配失败
    if(!L->elem)
        exit(OVERFLOW);
    //空表长度初始化为0；
    L->length = 0;
    //存储的初始容量为初始分配空间
    L->listsize = list_init_size;
    return OK;
}

int Input_Sq(SqList *L,int n)
{
    int i, *newbase;
    if(n<0)
        return ERROR;
    if( n > L->listsize )
    {
        newbase = (int *)malloc(listincreament * sizeof(int));
        if(!newbase)
            exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += listincreament;
    }
    printf("情输入元素：\n");
    for( i=0; i<n; i++)
    {
        scanf("%d", &L->elem[i]);
        L->length++;
    }
    return OK;
}


int ListInsert_Sq( SqList *L, int i, int e){
    //i需要满足1<=i<=ListLength_Sq(L)+1
    int *newbase;
    int *p;
    int *q;
    if( i < 1 || i > L->length + 1 ) return ERROR;
    if( L->length >= L->listsize ){ //当前存储空间已满,增加分配
        newbase = (int *) realloc( L->elem,( L->listsize+listincreament ) * sizeof(int) );
        if(!newbase) exit(OVERFLOW); //存储分配失败
        for(int j = 0; j<L->length ; j++)
        {
            newbase[j] = L->elem[j];
        }
        L->elem = newbase; //新基址
        L->listsize += listincreament; //增加存储容量
    }
    q = &(L->elem[i-1]); //q为插入的位置(注意数组的下标是从0开始计数)
    for(p = &(L->elem[L->length-1]) ;p >= q ; p--)
        *(p+1) = *p; //插入位置及之后的元素后移
    *q=e; //插入e
    L->length += 1; //表长增1
    return L->length;
}


int Output_Sq(SqList *L, int i)
{
    int j;
    printf("更新后的线性表为：\n");
    for(j=0; j<i; j++)
    {
        printf("%d\t",L->elem[j]);
    }
    return OK;
}
//在顺序线性表L中删除第i个元素,并用e返回其值
int ListDelete_Sq(SqList *L,int i,int *e){
    //i的合法性为1<=i<=ListLength_Sq(L)
    if( i<1 || i > L->length ) return ERROR;
    e = L -> elem[i-1];//把被删除的元素赋给e
    int *p = &L -> elem[i-1]; //指针p为被删除元素的位置
    for(int *q=p+1; q<=p+(L->length-i); q++) *(q-1) = *q; //被删除位置之后的元素都往前移
    L->length -= 1; //表长减一
    return OK;
}
int main()
{
    SqList MYL;
    char a;
    a='Y';
    int k, data, position, *e;
    InitList_Sq(&MYL);
    printf("请输入元素的个数: ");
    scanf("%d", &k);
    Input_Sq(&MYL, k);
    while(a == 'Y')
    {
        printf ("\n请输入要插入的元素：");
        scanf("%d",&data);
        printf("\n请输入要插入的位置：");
        scanf("%d",&position);
        ListInsert_Sq(&MYL,position,data);
        printf(&MYL.length);
        Output_Sq(&MYL,k+1);
        printf("\n请输入要删除的元素的位置： ");
        scanf("%d",&position);
        ListDelete_Sq(&MYL,position,e);
        Output_Sq(&MYL,k);
        printf("\n请问是否继续?(Y:继续 N:结束)\n");
        getchar();
        scanf("%c",&a);
    }
    system("pause");
    return OK;
}