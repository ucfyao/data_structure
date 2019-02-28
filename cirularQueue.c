// 循环队列
#ifndef queue_Header_h
#define queue_Header_h
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5

typedef enum
{
    OK=1, //正确
    ERROR=0,   //出错
    TRUE=1,  //为真
    FALSE=0   //为假
} status;

typedef struct 
{
    int * base;
    int rear;
    int front;
} cirularQueue;

// 初始化
void initQueue( cirularQueue *queue){
    queue->base = (int *)malloc(MAX_SIZE*sizeof(int));
    if (NULL == queue->base) {
        exit(0);
    }
    queue->front = queue->rear = 0;
}

// 长度
int getLength(cirularQueue queue){
    return (queue.rear - queue.front + MAX_SIZE) % MAX_SIZE;
}

// 入队，先判断是否满了
void pushQueue( cirularQueue *queue, int e){
    if((queue->rear + 1) % MAX_SIZE == queue->front){
        puts("循环队列是满的！");
    }else{
        queue->base[queue->rear] = e;
        queue->rear = (queue->rear + 1) % MAX_SIZE;
    }

}
// 出队
void popQueue(cirularQueue *queue){
    if(queue->front == queue->rear){
        puts("队列是空的！");
    }else{
        queue->front = (queue->front + 1) % MAX_SIZE;
    }
}

// 遍历
void traversal(cirularQueue queue){
    int q = queue.front;
    for (int i = 0; i < getLength(queue); i++) {
        printf("循环队列的第%d个元素为%d\n", i + 1, queue.base[q]);
        q++;
    }
}


#endif

int main(int argc, const char * argv[]) {
    cirularQueue queue;
    puts("循环队列初始化：");
    initQueue(&queue);
    pushQueue(&queue, 0);
    puts("循环队列元素1入队");
    pushQueue(&queue, 1);
    puts("循环队列元素2入队");
    pushQueue(&queue, 2);
    puts("循环队列元素3入队");
    pushQueue(&queue, 3);

    puts("循环队列元素遍历：");
    traversal(queue);

    puts("循环队列元素继续入队，无法完成：");
    pushQueue(&queue, 4);

    puts("循环队列元素0出队之后，先进先出原则：");
    popQueue(&queue);
    traversal(queue);

    puts("循环队列元素1出队之后，先进先出原则：");
    popQueue(&queue);
    traversal(queue);

    puts("循环队列元素2出队之后，先进先出原则：");
    popQueue(&queue);
    traversal(queue);

    puts("循环队列元素3出队之后，先进先出原则：");
    popQueue(&queue);
    traversal(queue);

    puts("4个元素全部删除，循环队列已经空了：");
    popQueue(&queue);
    traversal(queue);

    return 0;
}