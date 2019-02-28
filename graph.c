#pragma once
#include <stdio.h>
#include <stdlib.h>

/**
 * 图的操作
 * 本程序主要实现了对有向图，有向网，无向图，无向网。以及无向图的深度优先遍历，广度优先遍历，有向无环图的拓扑排序功能
 */

#define bool char
#define true 1
#define false 0
enum BOOL
{
    FALSE, TRUE
};
#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)

#define ElemType char
#define MAXQSIZE 50
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct ArcCell {
    int adj;         // 顶点关系类型 对于无权图 用0或1表示
    //char *info;     // 弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
    char vers[MAX_VERTEX_NUM]; // 用一个字符数组存储顶点向量
    AdjMatrix arcs;            // 邻接矩阵
    int vexnum, arcnum;        // 图的当前顶点数和弧数 
    GraphKind kind;            // 图的种类标志
    int in[MAX_VERTEX_NUM];    // 存放所有节点的入度
}MGraph;
// 图G中顶点v的第一个邻接点，不存在时返回 -1 
int FirstAdjVex(MGraph G, int v)
{

    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.arcs[v][i].adj)
        {
            return i;
        }
    }
    return -1;
}
// 图G中顶点v在w之后的下一个邻接点，不存在时返回 -1
int NextAdjVex(MGraph G, int v, int w)
{

    int i;
    for (i = w + 1; i < G.vexnum; i++)
    {
        if (G.arcs[v][i].adj)
        {
            return i;
        }
    }
    return -1;

}
// 深度优先遍历图
bool visited[MAX_VERTEX_NUM];
void DFS(MGraph G, int v)
{
    visited[v] = true;
    printf("%c", G.vers[v]);
    int j;
    for (j = 1; j <= G.vexnum; j++) {
        if (visited[j] == 0 && G.arcs[v][j].adj == 1)
        {
            DFS(G, j);// v每循环一次值都会变 上一轮的j值赋给了v
        }
    }
}

// 广度优先遍历
int BFSTraverse(MGraph G, int s)
{
    // 清空访问标志  
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
        visited[i] = false;
    // 定义队列，用于保存当前节点的邻接顶点  
    int Q[MAX_VERTEX_NUM];
    int front = 0;
    int rear = 0;
    int i, j;
    printf("%c", G.vers[s]);
    visited[s] = 1;
    Q[rear++] = s;
    // 遍历队列   
    while (front < rear)
    {
        i = Q[front++];
        for (j = 1; j <= G.vexnum; j++)
        {
            if (visited[j] == false && G.arcs[i][j].adj == 1)
            {
                printf("%c", G.vers[j]);
                visited[j] = true;
                Q[rear++] = j;
            }

        }
    }
    return 0;
}

// 定位顶点
int LocateVex(MGraph G, char v)
{
    int i;
    for (i = 0; i<G.vexnum; i++)
    {
        if (v == G.vers[i])
        {
            return i;
        }
    }
    return -1;

}

// 创建有向图
int CreateDG(MGraph G) {
    int i, j, k;
    char v1, v2;
    printf("请输入顶点数:");
    scanf("%d", &G.vexnum);
    printf("\n请输入弧数:");
    scanf("%d", &G.arcnum);
    printf("请输入%d个顶点：(每个顶点之间用空格隔开)", G.vexnum);
    fflush(stdin);
    getchar(); 
    for (i = 0; i < G.vexnum; i++)
    {
        scanf("%c", &G.vers[i]);
        // 注意数组vers[i]的初始大小为20
        getchar();  
    }
    // 打印输出各个顶点
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%c", G.vers[i]);

    }
    printf("\n");
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j].adj = INFINITY;
        }
    }
    //入度初始化
    for (int i = 0; i < G.vexnum; i++)
    {
        G.in[i] = 0;
    }
    for (k = 0; k < G.arcnum; k++)
    {
        printf("\nplease input <v1 v2>:");
        fflush(stdin);
        // v1 v2 之间用空格隔开
        scanf("%c %c", &v1, &v2);
        // 清除残余后，后面再读入时不会出错
        fflush(stdin);
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G.arcs[i][j].adj = 1;
        G.in[j]++;
        getchar();
    }
    return 1;
}

// 创建有向网
int CreateDN(MGraph G) {
    int i, j, k, w;
    char v1, v2;
    printf("请输入顶点数：");
    scanf("%d", &G.vexnum);
    printf("\n请输入弧的数目:");
    scanf("%d", &G.arcnum);
    printf("请输入%d个顶点：(每个顶点之间用空格隔开)", G.vexnum);
    fflush(stdin);
    getchar();
    for (i = 0; i < G.vexnum; i++)
    {
        scanf("%c", &G.vers[i]);
        // 注意数组vers[i]的初始大小为20
        getchar();  
    }
    // 打印输出各个顶点
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%c", G.vers[i]);
    }
    printf("\n");
    // 初始化邻接矩阵
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j].adj = INFINITY;

        }
    }
    for (k = 0; k < G.arcnum; k++)
    {
        printf("\n please input <v1 v2 w>:");
        fflush(stdin);
        // v1 v2 w之间用空格隔开
        scanf("%c %c %d", &v1, &v2, &w);
        // 清除残余后，后面再读入时不会出错
        fflush(stdin);
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G.arcs[i][j].adj = w;

        getchar();
    }
    return 1;
}

// 创建无向图
int CreateUDG(MGraph G)
{
    int i, j, k;
    char v1, v2;
    printf("请输入顶点数:");
    scanf("%d", &G.vexnum);
    printf("\n请输入边数:");
    scanf("%d", &G.arcnum);
    printf("请输入%d个顶点：(每个顶点之间用空格隔开)", G.vexnum);
    fflush(stdin);
    getchar();
    for (i = 0; i < G.vexnum; i++)
    {
        scanf("%c", &G.vers[i]);
        // 注意数组vers[i]的初始大小为20
        getchar(); 
    }
    // 打印输出各个顶点
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%c", G.vers[i]);

    }
    printf("\n");
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j].adj = INFINITY;
        }
    }
    for (k = 0; k < G.arcnum; k++)
    {
        printf("\nplease input <v1 v2>:");
        fflush(stdin);
        // v1 v2 之间用空格隔开
        scanf("%c %c", &v1, &v2);
        // 清除残余后，后面再读入时不会出错
        fflush(stdin);
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G.arcs[i][j].adj = 1;
        G.arcs[j][i].adj = 1;
        getchar();
    }
    return 1;
}

// 创建无向网
int CreateUDN(MGraph G)
{
    int i, j, k, w;
    char v1, v2;
    printf("请输入顶点数：");
    scanf("%d", &G.vexnum);
    printf("\n请输入边的数目:");
    scanf("%d", &G.arcnum);
    printf("请输入%d个顶点：(每个顶点之间用空格隔开)", G.vexnum);
    fflush(stdin);
    getchar();
    for (i = 0; i < G.vexnum; i++)
    {
        scanf("%c", &G.vers[i]);
        // 注意数组vers[i]的初始大小为20
        getchar();  
    }
    // 打印输出各个顶点
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%c", G.vers[i]);

    }
    printf("\n");
    // 初始化邻接矩阵
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j].adj = INFINITY;
        }
    }
    for (k = 0; k < G.arcnum; k++)
    {
        printf("\n please input <v1 v2 w>:");
        fflush(stdin);
        // v1 v2 w之间用空格隔开
        scanf("%c %c %d", &v1, &v2, &w);
        // 清除残余后，后面再读入时不会出错
        fflush(stdin);
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G.arcs[i][j].adj = w;
        G.arcs[j][i].adj = w;
        getchar();
    }
    return 1;
}
// 栈类型
typedef int SElemType;
// 存储空间初始分配量
#define STACK_INIT_SIZE1 10
// 存储空间分配增量
#define STACKINCREMENT1 2                                        

// 栈的顺序存储结构表示
typedef struct SqStack1
{
    SElemType *base;                        // 基地址
    SElemType *top;                         // 栈顶指针
    int stacksize1;                         // 当前已经分配的存储空间
}SqStack1;

// 构造一个空栈
int InitStack1(SqStack1 S)
{
    // 为栈底分分配一个指定大小的存储空间
    S.base = (SElemType *)malloc(STACK_INIT_SIZE1 * sizeof(SElemType));
    if (!S.base){
        exit(0);
    }
    // 栈底与栈顶指针相同
    S.top = S.base;                   
    S.stacksize1 = STACK_INIT_SIZE1;
    return 1;
}


// 若栈S为空栈（栈底指针和栈顶指针相同）, 则返回1，否则返回0
int StackEmpty1(SqStack1 S)
{
    if (S.top == S.base){
        return 1;
    }else{
        return 0;
    }
}


// 插入元素e为新的栈顶元素
int Push(SqStack1 *S, SElemType e)
{
    if ((*S).top - (*S).base >= (*S).stacksize1)
    {
        (*S).base = (SElemType *)realloc((*S).base, ((*S).stacksize1 + STACKINCREMENT1) * sizeof(SElemType));
        if (!(*S).base)
            exit(0);
        (*S).top = (*S).base + (*S).stacksize1;
        (*S).stacksize1 += STACKINCREMENT1;
    }
    *((*S).top)++ = e;
    return 1;
}

// 若栈不为空，则删除S栈顶元素用e返回其值，并返回1，否则返回0
int Pop(SqStack1 *S, SElemType *e)
{
    if ((*S).top == (*S).base)
    {
        return 0;
    }
    *e = *--(*S).top;
    return 1;
}
// 有向图的拓扑排序
void TopologicalSort(MGraph G)
{
    int i, j,k;
    int count = 0;
    SqStack1 S;
    InitStack1(S);
    for (i = 0; i<G.vexnum; i++)
    {
        if (G.in[i] == 0)
        {
            Push(&S, i);
        }
    }
    while (!StackEmpty1(S))
    {
        Pop(&S, &k);
        printf("%c->", G.vers[k]);
        count++;
        for (i = 0; i < G.vexnum; i++)
        {
            if (G.arcs[k][i].adj == 1)
            {
                G.in[i]--;
                if (G.in[i] == 0)
                {
                    Push(&S, i);
                }
            }
        }
    }
    // 如果计算得到的拓扑排序的节点数目小于总的，说明不是连通图
    if (count < G.vexnum)
    {
        printf("此图是有环路的\n");
    }
    else
    {
        printf("此图是没有环路的\n");
    }

}

int main(){

}