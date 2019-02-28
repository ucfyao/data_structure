#include<stdio.h>
#include<stdlib.h>
#define CAPACITY 20

/*
 * 堆有两个性质：
 * 1.结构性：堆必须是一颗完全二叉树
 * 2.堆序性：堆的父节点要么都大于子节点，要么小于子节点，前者叫大顶堆，后者叫小顶堆；
 * 由此，堆可以用一个数组来表示，并有如下性质：
 * 1.对于任意i位置的元素，他的左子节点在2i位置，右子节点在2i+1位置；
 * 2.他的父节点（假如有）在i/2位置
 * 
 */

 // 创建一个小顶堆，size 代表的是实际元素的个数
 typedef struct MinHeap
 {
     int size;
     int data[CAPACITY];
 } heap;

void init( heap *h);
void insert( heap *h,int x);
void travel( heap *h);

void init( heap *h){
    h->size = 0;
}

void insert(heap *h, int x){
    if(h->size == CAPACITY){
        printf("heap is full!");
        return ;
    }
    int i ;
    h->size++;
    for( i = h->size; i >= 1; i /= 2){
        if( x < h->data[i/2]){
            h->data[i] = h->data[i/2];
        }else{
            break;
        }
    }
    h->data[i] = x;
}

/* 
 * 删除最小元素，在小顶堆即意味着删除根节点
 * 1.首先将根元素保存，等待最后return；
 * 2.将最后一个元素赋值给根元素，并将这个值赋给缓冲区，这样保证了堆的结构性；
 * 3.从根节点开始遍历，比较父节点和两个子节点的大小，如果缓冲区值大于较小的子节点，则将小节点的值赋给父节点
 * 4.直到缓冲区值小于游标的两个子节点，此时将缓冲区值赋给游标所在位置
 */
int deleteMin(heap *h){
    int child;
    int result = h->data[1];
    h->data[1] = h->data[h->size];
    h->size--;
    int i = 1;
    int temp = h->data[1];
    for(i = 1; 2*i <= h->size; i = child) {
        child = 2 * i;
        /*如果左子节点非最后元素且>右子节点,则右子节点最小*/
        if(child != h->size && h->data[child] > h->data[child+1] ) {
            child++;
        }
        /*如果temp大于当前元素的最小子节点，则将最小子节点赋值给父节点，否则跳出*/
        if(temp > h->data[child]) {
            h->data[i] = h->data[child];
        } else {
            break;
        }
    }
    h->data[i] = temp;/*将缓冲区值赋给当前游标*/
    return result;
}

/*遍历堆数组：越过空白位置0，从1开始*/
void travel(heap *h) {
    int i;
    for(i = 1; i <= h->size; i++) {
        printf("%d ",h->data[i]);
    }
    printf("\n");
}

// 堆排序
void sort(int a[],int n){
    int i;
    /*给堆指针分配空间*/
    heap *h = (heap*)malloc(sizeof(heap));
    /*初始化堆*/
    init(h);
    /*将数组的元素依次插入堆*/
    for(i = 0; i < n; i++) {
        insert(h,a[i]);
    }
    for(i = 0; i < n; i++) {
        a[i] = deleteMin(h);
    }
}

/*遍历数组*/
void travel_array(int a[],int n) {
    int i ;
    for( i = 0; i < n; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

int main(){
    int a[] = {12,2,3,68,120,90,10,36,19,123,22,11,5,60,8,91};
    printf("%ld \n", sizeof(a));
    printf("%lu \n",sizeof(int));
    int n = sizeof(a) / sizeof(int);
    printf("%d \n", n);

    travel_array(a,n);
    sort(a,n);
    travel_array(a,n);
}
