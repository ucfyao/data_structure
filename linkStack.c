#include <stdio.h>
#include <stdlib.h>

#define true  1
#define false 0 
// 链栈是一种特殊的线性链表。和所有链表一样，是动态存储结构，无需预先分配存储空间。先入后出，采用头插法。

typedef struct node
{
    int data;
    struct node *next;
} LinkStackNode;

typedef struct
{
    LinkStackNode *top;
    int length;
} LinkStack;

// 初始化
void initLinkStack(LinkStack *s){
    s->top = NULL;
    s->length = 0;
}

// 判断栈是否为空
int isEmpty(LinkStack *s){
    if(s->length == 0){
        return true;
    }else{   
        return false;
    }
}
// 入栈
int pushLinkStack(LinkStack *s, int value){
    LinkStackNode * temp = (LinkStackNode *) malloc(sizeof(LinkStackNode));
    if(temp == NULL){
        return false;
    }
    temp->data = value;
    temp->next = s->top;
    s->top = temp;
    s->length ++;
    printf("入栈成功! \n");
    return true;
}
// 出栈
int popLinkStack(LinkStack *s, int * value){
    if(isEmpty(s)){
        printf("is empty!");
        return false;
    }
    LinkStackNode * temp = s->top;
    s->top = temp->next;
    s->length --;
    *value = temp->data;
    free(temp);
    printf("出栈成功! \n");
    return false;
}

// 获取栈顶数据
int topLinkStack( LinkStack *s, int *value){
    if(isEmpty(s) == true){
        printf("出栈成功! \n");
        return false;
    }
    *value = s->top->data;
    return true;
}
// 输出栈中元素
int printfLinkStack(LinkStack *s){
    LinkStackNode *w;
    printf("栈中的元素有：");
    w = s->top;
    while( w->next){
        printf("%d ",w->data);
        w = w->next;
    }
    printf("%d ",w->data);
    printf("\n");
}
// 菜单
void menu(){
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
int main(){
    LinkStack *s;
    int i, e = -1,x;
    while( e == -1){
        menu();
        scanf("%d", &i);
        puts("");
        switch(i){
            case 1 :
                initLinkStack(s);
                printf("初始化完成！\n");
                break;
            case 2 :
                printf("%d\n",isEmpty(s));
                break;
            case 3:
                printf("请输入需要入栈的数据：");
                scanf("%d",&x);
                pushLinkStack(s,x);
                break;
            case 4:
                printfLinkStack(s);
                break;
            case 5:
                popLinkStack(s,&x);
                break;
            case 6:
                topLinkStack(s,&x);
                printf("栈顶元素为：%d\n",x);
                break;
            case 0:
                e = 0;
                break;
            default:printf("选择有误，请重新选择 \n");
        }
    }
    return 0;
}