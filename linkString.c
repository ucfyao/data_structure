#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    // 字符域
    char ch;
    // 指针域，存放下一个结点的地址
    struct node *next;
} linkStr;

linkStr * initString(){
    linkStr *s;
    s = (linkStr *) malloc(sizeof(linkStr));
    if(s != NULL){
        s->next = NULL;
    }
    return s;
}

// 判断空单
int isEmpty(linkStr *s){
    if( s->next == NULL){
        return 1;
    }else{
        return 0;
    }
}

// 赋值操作
void assign(linkStr *str,char t[]){
    linkStr *tmp1,*tmp2,*tmp3;
    // r 始终表示的是尾结点（最后一个非空节点，而不是最后一个NULL节点）
	tmp3 = str;
    tmp2 = str->next;
    int i;
    for( i = 0; t[i] != '\0'; i++){
        if(tmp2 != NULL){
            tmp2->ch = t[i];
            tmp3 = tmp2;
            tmp2 = tmp2->next;
        }else{
            // 初始化时只给头结点分配了存储空间或者其他情况。如果需要继续添加数据，需要继续分配。
            tmp1 = (linkStr *) malloc (sizeof(linkStr));
            // 添加节点
            tmp1->ch = t[i];
            tmp3->next = tmp1;
            tmp3 = tmp1;
        }
        tmp3->next = NULL;
    }

    // 将s中原来多余的空间释放掉
    while(tmp2 != NULL){
		tmp1 = tmp2->next;
        free(tmp2);
        tmp2 = tmp1;
    }
}

// 串拷贝操作
void copy(linkStr *s, linkStr *t ){
    // 将t串的值赋值给s串
    linkStr *p, *q, *r, *u;
    p = t->next;
    q = s->next;
    r = s;
    while(p != NULL){
        // 串s原先分配了空间
        if(q != NULL){
            q->ch = p->ch;
            r = q;
            q = q->next;
        }else{
            u = (linkStr *)malloc(sizeof(linkStr));
            u->ch = p->ch;
            r->next = u;
            r = u;
        }
        // p节点后移
        p = p->next;
    }
    // 若q的长度过长，可以释放多余的空间
    while( q != NULL){
        p = p->next;
        free(q);
        q = p;
    }
    r->next = NULL;
}

// 求串的长度
int length(linkStr *s){
    linkStr *p;
    int n = 0;
    p = s->next;
    while(p != NULL)
    {
        n++;
        p = p->next;
    }
    return n;
}

// 串的连接操作
void contact(linkStr *s,linkStr *s1,linkStr *s2){
    linkStr *p, *q, *r, *t;
    r = s;
    p = s1->next;
    q = s->next;
    while( p != NULL ){
        if( q != NULL ){
            q->ch = p->ch;
            q = q->next;
            r = q;
        }else{
            t = (linkStr *) malloc(sizeof(linkStr));
            t->ch = p->ch;
            r->next = t;
            r = t;
        }
        p = p->next;
    }
    p = s2->next;
    while( p != NULL){
        if(q != NULL){
            q->ch = p->ch;
            q = q->next;
            r = q;
        }else{
            // 串s原来没有分配存储空间，需要申请空间
            t = (linkStr *) malloc (sizeof(linkStr));
            t->ch = p->ch;
            r->next = t;
            r = t;
        }
        p = p->next;
    }
    // 将串s的多余的空间清除掉(这个情况只可能发生在while的if循环中)
    while (q != NULL){
        p = q->next;
        free(q);
        q = p;
    }
    r->next = NULL;
}

// 取子串操作
int substr(linkStr *s,int i,int len,linkStr *t){
    linkStr *p, *q, *r, *u;

    if(i <= 0 || i > length(s) || i + len - 1 > length(s)){
        return 0;
    }

    // 指针指向s的第i-1个位置
    int j,k;
    for(j=0, p = s; j<i; j++){
        p = p->next;
    }
    
    for(k = 0, r = t, q = t->next; k<len; k++){
        if(q != NULL){
            q->ch = p->ch;
            r = q;
            q = q->next;
        }else{
            u = (linkStr *) malloc (sizeof(linkStr));
            u->ch = p->ch;
            r->next = u;
            r = u;
        }
        p = p->next;
    }

    while(q != NULL){
        p = q->next;
        free(q);
        q = p;
    }
    r->next = NULL;
    return 1;
}

// 插入操作
int insert(linkStr *s, int i, linkStr *t){
    linkStr *p, *q, *r;
    if(i<=0 || i> length(s) +1){
        return 0;
    }
    int j;
    for(j = 0, p = s; j < i - 1; j++)
    {
        p = p->next;
    }
    q = t->next;

    while( q != NULL){
        r = (linkStr *) malloc (sizeof(linkStr));
        r-> ch = q->ch;
        r->next = p->next;
        p->next = r;
        q = q->next;
        p = r;
    }
    return 1;
}

// 删除操作
int delete(linkStr *s, int i, int len){
    linkStr *p, *q, *r;
    if(i<=0 || i>length(s) || i + len -1 >length(s)){
        return 0;
    }
    int j;
    for(j = 0, p = s; j < i-1; j++){
        p = p->next;
    }
    for(j = 0; j<len; j++){
        q = p->next;
        p->next = q->next;
        free(q);
    }
    return 1;
}

// 输出
void print(linkStr *s){
    linkStr *p = s->next;
    while (p != NULL){
        printf("%c", p->ch);
        p = p->next;
    }
    printf("\n");
}

int main(){
    linkStr *s1 = NULL;
    linkStr *s2 = NULL;
    linkStr *s3 = NULL;
    s1 = initString();
    s2 = initString();
    s3 = initString();

    char str[100];
    printf("请输入字符串：\n");
    gets(str);
    assign(s1,str);
    printf("串 s1 为：");
    print(s1);
    printf("串 s1 长度为：%d\n", length(s1));
    copy(s2,s1);

    printf("串 s2 为：");
    print(s2);
    
    printf("串s2删除操作(第三个位置的三个字符删除 ：");
    delete(s2,3,3);
    print(s2);

    printf("串连接操作（s3=s1+s2 ）：");
    contact(s3,s1,s2);
    print(s3);
    printf("插入操作(从s1的第6个位置插入s3)：");
    insert(s1,6,s3);
    print(s1);

    printf("测试截取子串的功能s2（截取s3的第四个位置长度为4的字符串：");
    substr(s3,4,4,s2);
    print(s2);
    
    printf("测试字Contact的清除过多存储空间的功能：(将两个较短的字符[两个s2]合并写到s1上去：");
    contact(s1,s2,s2);
    print(s1);
}