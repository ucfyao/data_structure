//表头删除元素，在表尾插入元素.先进先出 (FIFO = first in first out )   
// 分为几种：
// 1.双端队列。限定插入和删除在表的两端进行，也是先进先出 (FIFO)结构。（1）输入受限的双端队列：一个端点可插入和删除，另一个端点仅可删除。（2）输出受限的双端队列：一个端点可插入和删除，另一个端点仅可插入。（3）等价于两个栈底相连接的栈：限定双端队列从某个端点插入的元素，只能在此端点删除。
// 2.链式队列。用链表表示的队列，限制仅在表头删除和表尾插入的单链表。
// 3.顺序队列。
// 4.循环队列。

// 链式队列

#ifndef queue_Header_h
#define queue_Header_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef enum
{
    OK=1, //正确
    ERROR=0,   //出错
    TRUE=1,  //为真
    FALSE=0   //为假
} status;

typedef int ElemType;
// 队列节点结构
typedef struct Node
{
    ElemType data;
    struct Node * next;
} LQNode;
// 链式队列结构
typedef struct 
{
    LQNode *front;
    LQNode *rear;
} LinkQueue;

// 创建空队列： pQHead即为队列头结点
status initQueue(LinkQueue * pQHead){
    // 队列头结点的队头和队尾指针申请内存
    pQHead ->front = pQHead->rear = (LQNode *) malloc (sizeof(LQNode));
    // 检测是否申请成功
    if(!pQHead ->front){
        return FALSE;
    }
    //设置头结点指针域为空
    pQHead ->front->next = NULL;
    return OK;
}
// 销毁队列
void destroyQueue(LinkQueue *pQHead){
    free(pQHead->front);
    free(pQHead->rear);
    pQHead->front = pQHead->rear = NULL;
}

// 清空队列
void clearQueue(LinkQueue *pQHead){
    pQHead->front = pQHead->rear;
}
// 判断队列是否为空
status isEmpityQueue(LinkQueue *pQHead)
{
    //队头指针与队尾指针相等，说明队列为空
    if(pQHead->front == pQHead->rear){
        return TRUE;
    }
    return FALSE;
}
// 获得队列长度
int getQueueLen(LinkQueue *pQHead){
    LQNode *temp = pQHead->front;
    int length = 0;
    while(temp != pQHead->rear)
    {
        ++length;
        temp = temp->next;
    }
    return length;
}
// 新元素入队列。链式队列的尾结点指针，指向存放新元素的新结点
status pushQueue(LinkQueue * pQHead,ElemType element){
    LQNode *temp = (LQNode *) malloc(sizeof(LQNode));
    if(!temp){
        printf("temp malloc error!\n");
        return FALSE;
    }
    // 将要插入元素存入新结点的数据域内
    temp->data = element; 
    // 队列只能从队尾插入所以下一个结点初始化为NULL
    temp->next = NULL;
    // 链式队列元素为结点(LQNode)
    // 使前一个结点的next指向新结点,pQHead->rear为队列的最后一个结点，当插入新结点temp时,pQHead->rear->next = temp
    pQHead->rear->next = temp;
    // pQHead->rear总是指向队列的最后一个结点
    pQHead->rear = temp;
    return OK;
}
// 出队列
status popQueue(LinkQueue *pQHead,ElemType *pElement){
    // 如果队列为空，则返回error
    if(isEmpityQueue(pQHead) == TRUE)
    {
        printf("queue is NULL!\n");
        return ERROR;
    }
    LQNode *temp = pQHead->front->next;
    // 如果出队的节点为最后一个节点，那么使指针指向最后头节点，防止出现悬空的指针
    if (pQHead->front->next == pQHead->rear ) {
        pQHead->rear = pQHead->front;
    }
    // 将出队的数据元素存入*e
    *pElement = temp->data;
    // 使下一个结点成为队头,如果没有下一个结点则为NULL
    pQHead->front->next = temp->next;
    // 删除要出队的结点
    free(temp); 
    temp = NULL;
    return OK;

}

// 遍历队列
void traverseQueue( LinkQueue * pQHead){
    // 如果队列为空
    if(isEmpityQueue(pQHead)==TRUE)
    {
        printf("\nqueue is NULL!\n");
        return ;
    }
    LQNode *temp = pQHead->front;
    printf("将队列中的所有元素出队:\n");
    while(temp != pQHead->rear){
        temp = temp->next;
        printf("%d  ", temp->data);
    }
    printf("\n");

}
int main(){
    // 用于保存出队的元素
    int value;
    // 给头结点申请内存
    LinkQueue *pQHead = (LinkQueue*)malloc(sizeof(LinkQueue));
    if(!pQHead) //检测是否申请失败
    {
        printf("pQHead malloc error!\n");
        return ERROR;
    }
     //调用初始化队列的函数
    initQueue(pQHead);
    //调用入队函数
    pushQueue(pQHead, 1);
    pushQueue(pQHead, 2);
    pushQueue(pQHead, 3);

    //调用遍历队列的函数
    traverseQueue(pQHead);

    //调用出队函数
    if(popQueue(pQHead, &value)==OK)
    {
        printf("出队一次，元素为：%d\n", value);
    }

    traverseQueue(pQHead);

    printf("队列长度是%d\n",getQueueLen(pQHead));
    clearQueue(pQHead);   //清空队列
    traverseQueue(pQHead);
    free(pQHead);
    pQHead = NULL;

    return 0;


}
#endif