#include <stdio.h>
#include <stdlib.h>

#define true  1
#define false 0 
// 栈只能在一端进行插入、删除操作。后入先出（LIFO，last in first out）。
// 两种实现方式。顺序栈，链栈。

// 顺序栈：一组地址连续的存储单元。依次存放栈底到栈顶的数据元素，栈底位置固定不变，栈顶位置随着入栈和出栈操作而变化。
#define MAXSIZE 10
// 顺序栈的结构
typedef struct
{
    int data[MAXSIZE];
    int top;
} SeqStack;
// 初始化
void initSeqStack(SeqStack *s){
    s->top = -1;
}
// 判断是否为空
int isEmpty(SeqStack *s){
    if(s->top == -1 ){
        return true;
    }else{
        return false;
    }
}
// 入栈
void pushSeqStack(SeqStack *s, int x){
    if( s->top == MAXSIZE-1){
        printf("Stack is full\n");
    }else{
        s->top++;
        s->data[s->top] = x;
        printf("入栈成功! \n");

    }
}
// 出栈
void popSeqStack(SeqStack *s, int *x){
    if(isEmpty(s)){
        printf("Stack is empty\n");
    }else{
        *x = s->data[s->top];
        s->top--;
        printf("出栈成功! \n");

    }
}

// 获取栈顶数据
void topSeqStack(SeqStack *s,int *x){
    if(s->top == -1){
        *x = false;
        printf("栈为空! \n");
    }else{
        *x = s->data[s->top];
        printf("获取栈顶数据成功！\n");
    }

}
// 输出
void printfSeqStack(SeqStack *s){
    int i;
    printf("栈中的元素有：");
    for( i = s->top; i >= 0; i--)
    {
        printf("%d",s->data[i]);
    }
    printf("\n");    
}

void memu(){
    puts("****************");
    puts("1.初始化");
    puts("2.判断栈为空");
    puts("3.入栈");
    puts("4.输出栈中元素");
    puts("5.出栈");
    puts("6.取栈顶元素");
    puts("****************\n");
    printf("Your choice is:");
}

// 主函数
int main()
{
    SeqStack *s;
    int  e=-1, i;
    while(e == -1)
    {
        int x ;
        memu();
        scanf("%d",&i);
        puts("");
        switch(i)
        {
            case 1:
                initSeqStack(s);
                printf("初始化完成！\n");
                break;
            case 2:
                printf("%d\n", isEmpty(s));
                break;
            case 3:
                printf("请输入需要入栈的数据：");
                scanf("%d", &x);
                pushSeqStack(s, x);
                break;
            case 4:
                printfSeqStack(s);
                break;
            case 5:
                popSeqStack(s, &x);
                break;
            case 6:
                topSeqStack(s, &x);
                printf("栈顶元素为：%d\n",x);
                break;
            case 0:
                e = 0;
                break;
            default:printf("选择有误，请重新选择\n");
        }
    }

    return 0;
}

// 链栈是一种特殊的线性链表。和所有链表一样，是动态存储结构，无需预先分配存储空间。
