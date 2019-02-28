//单链表的创建、插入元素、删除元素、元素定位、求表长等操作； 
#include <stdio.h>
// #include "stdafx.h"
#include <stdlib.h>

#define true  1
#define false 0 
typedef int ElemType;

typedef struct node
{
    ElemType data;
    struct node *next;
} Slink;

// 创建一个含n个元素的带头结点的单链表
Slink *createSlink(int n){
    Slink *head, *current, *s;
    int i;
    current = head = (Slink *) malloc(sizeof(Slink));   // 创建头结点
    printf("请输入%x个值:\n",n);
    for(int i = 0; i < n; i++)
    {
        s = (Slink *) malloc(sizeof(Slink));
        scanf("%d", &s->data);
        current->next = s; // 将新节点s插入链表的尾结点
        current = s; // 修改尾指针指向current指向当前的尾结点s
    }
    current->next = NULL;
    return head;
}
// 清空链表
void clearList(Slink *head){
    // 最终效果是只保留头节点。
    Slink *p;
    while(head->next){
        p = head->next;
        head->next = p->next;
        free(p);
    }
}
// 销毁链表
int destroy(Slink *head){
    Slink *temp;
    while(head){
        temp = head->next;
        free(head);
        head = temp;
    }
    // clearList(head);
    // free(head);

    head = NULL;
    return true;
}
// 表长操作
int getSlinkSize(Slink *head){
    Slink *current = head;
    int size = 0;
    
    while (current->next != NULL){
        current = current->next;
        size++;
    }
    return size;
}

// 插入元素操作(在带头结点的单链表head中的第i个节点前插入元素x）
int insertSlink(Slink *head, int i, ElemType x){
    Slink *current, *s;
    int j = 0;
    if( i<1 ) return false;
    current = head;
    while( current != NULL && j < i-1 ){
        j++;
        current = current->next;
    }
    if(current == NULL) return false; // 表示超过表的长度
    s = (Slink *) malloc (sizeof(Slink)); // 创建新节点s
    s->data = x;
    s->next = current->next;
    current->next = s;
    return true;
}
// 删除元素(删除带头节点单链表head的第i个节点）
int deleteSlink(Slink *head, int i, ElemType *e){
    Slink *current, *rear;
    int j = 0;
    if( i<1 ){
        return false;
    }
    current = head;
    while (current->next != NULL && j<i-1)
    {
        j++;
        current = current->next; 
    }
    if(current->next == NULL){
        return false;
    }
    rear = current->next;   // 令rear尾指针指向第i个节点
    current->next = rear->next;
    *e = rear->data;
    free (rear);   // 释放掉第i个节点所占用的内存空间
    return true;
}
// 查找元素
Slink *locSlink(Slink *head , ElemType x){
    Slink *current = NULL;
    int i;
    current = head;
    while (current->next != NULL && current->data != x ){
        i++;
        current = current->next;
    }
    return current;
}

// 输出操作
void printSlink(Slink *head){
    Slink *current = NULL;
    current = head->next;
    while(current != NULL){
        printf("%d ",current->data);
        current = current->next;
    }
    printf("\n");
    return;
}

// 链表的三种排序（选择，插入，冒泡）
int selectionSort(Slink *head){
    // 选择排序。每次取出剩下元素的最大值（或最小值）放在当前位置。
    int t = 0;
    int size = getSlinkSize(head);
    for(Slink *temp = head->next; temp != NULL; temp = temp->next)
    {
        for(Slink *p = temp; p != NULL; p = p->next)
        {   
            if(temp->data > p->data){   
                printf("换%d和%d\n", temp->data, p->data);
                t = temp->data;
                temp->data = p->data;
                p->data = t;
            }
        }
    }
    return true;
}
// 插入排序，每次将要遍历的数插入到前边数列的合适位置，保证已经遍历的元素为有序数列。
int insertSort(Slink* head){
    int t = 0;
    for(Slink *temp = head->next->next; temp != NULL; temp = temp->next)
    {
        for(Slink *p = head; p->next != NULL; p = p->next){
            if (p->next->data > temp->data) {
                printf("换%d和%d\n", temp->data, p->next->data);
                t = temp->data;
                temp->data = p->next->data;
                p->next->data = t;
            }
        }
    }
    return true;
}
// 冒泡排序，相邻之间进行比较，如果大于，进行交换
// 优化
// 每遍历一遍，末尾就得到一个最大值，接下来每次都减少一个元素就好了
// 遍历n-1遍就排好序了，因为最后一遍只剩一个元素了，
int bubbleSort(Slink* head){
    int t = 0;
    for(Slink * temp = head->next; temp->next != NULL; temp = temp->next)
    {
        for(Slink *p = head->next;  p->next != NULL; p = p->next){
            if(p->data > p->next->data){
                printf("换%d和%d\n", p->data, p->next->data);
                t = p->data;
                p->data = p->next->data;
                p->next->data = t;
            }
        }
    }
    
    return true;
}
int main(void){
    Slink *mslink = NULL;
    ElemType a;
    int m;
    printf("创建x长的链表:");
    scanf("%d",&m);
    mslink = createSlink(m);
    printf ("length:%d\n",getSlinkSize (mslink));
    printSlink (mslink);
    // printf("请输入要插入的位置和数据:");
    // int in,inData;
    // scanf("%d%d",&in,&inData);
    // insertSlink (mslink, in, inData);
    // printSlink (mslink);
    // deleteSlink (mslink, 4, &a);
    // printSlink (mslink);
    // selectionSort (mslink);
    // insertSort (mslink);
    bubbleSort (mslink);
    printSlink (mslink);

    // clearList(mslink);
    // printSlink(mslink);

    destroy(mslink);
    printSlink(mslink);
    // printf("链表已经销毁 %s",mslink);
    // system ("pause");
    return 0;
}