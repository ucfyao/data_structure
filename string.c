#include<stdio.h>
#include<stdlib.h>

# define MAXSIZE 100

typedef struct st
{
    // 串存放的起始地址，串中第i个字符存储在ch[i-1]中
    char *ch;
    // 串的长度
    int length;
    // 分配的存储空间的大小，如果不足，在通过realloc()分配增加空间
    int strsize;

} string;

string initString(){
    string s;
    s.length = 0;
    s.ch = (char *) malloc(MAXSIZE *sizeof(char));
    s.strsize=MAXSIZE;

    return s;
}

// 判断空单
int isEmpty(string s){
    if( s.length == 0){
        return 1;
    }else{
        return 0;
    }
}

// 赋值操作
void stringAssign(string *s1,char s2[]){
    int i = 0;
    while(s2[i] != '\0'){
        i++;
    }
    if(i>s1->strsize){
        //所赋值的字符数组超过字符串的默认容量，则增加存储空间
        s1->ch = (char*)malloc(i*sizeof(char));
        s1->strsize = i;
    }
    s1->length = i;
    for(i=0;i<s1->length;i++){
        s1->ch[i] = s2[i];
    }

}

// 串拷贝操作
void stringCopy(string *s1,string s2){
    if(s1->strsize < s2.length){
        s1->ch = (char *) realloc(s1->ch,s2.length * sizeof(char));
        s1->strsize = s2.length;
    }
    s1->length = s2.length;
    int i;
    for(i = 0;i<s1->length ; i++){
        s1->ch[i] = s2.ch[i];
    }
}

// 求串的长度
int stringLength(string s){
    return s.length;
}

// 串的连接操作
void contact(string *s, string s1, string s2){
    if(s->strsize < s1.length + s2.length){
        s->ch = (char *)realloc(s->ch,(s1.length+s2.length)*sizeof(char));
        s->strsize=s1.length+s2.length;
    }
    s->length = s1.length +s2.length;
    int i;
    // 将s1复制到s中
    for(i=0; i<s1.length; i++){
        s->ch[i] = s1.ch[i];
    }  
    // 将s2复制到s中去
    for(; i<s->length; i++){
        s->ch[i] = s2.ch[i - s1.length];
    }
}

// 取子串操作
int substr(string s,int i,int len,string *t){
    /*
        i表示从字符串s的第i个位置开始截取（索引从1开始）
        len表示截取字符串的长度
    */
    if(i <= 0 || i > s.length || len < 0 || len > s.length-i+1){
        return 0;
    }
    // 存储空间不够，继续分配存储空间
    if(t->length < len){
        t->ch = (char *) realloc (t->ch, len * sizeof(char));
        t->strsize = len;
    }

    t->length = len;
    int k;
    for(k=0;k<t->length;k++){
        t->ch[k] = s.ch[i-1+k];
    }

    return 1;
}

// 插入操作
int insertString(string * s, int i, string t){
    // 在字符串s的第i个位置插入字符串t
    if( i <= 0 || i > s->length+1){
        return 0;
    }
    if(s->strsize < s->length + t.length){
        s->ch = (char *) realloc(s->ch ,(s->length + t.length) * sizeof(char));
        s->strsize = s->length + t.length;
    }
    int k ;
    // 将s中的后i个字符后移到后面
    for(k = s->length - 1;k >= i-1;k--){
        s->ch[k + t.length] = s->ch[k];
    }
    s->length = s->length + t.length;
    //将t的值赋值给s
    for(k = 0; k < t.length; k++ ){
        s->ch[k+i-1] = t.ch[k];
    }
    return 1;
}

// 删除操作
int deleteString(string *s, int i, int len){
    // 从s的第i个字符开始删除len个字符
    if(i<=0 || i>s->length  || len<0 || len>s->length-i+1){
        return 0;
    }
    int k ;
    // 从s的i+len-1个位置开始将其后的所有字符前移
    for( k = i + len - 1; k < s->length; k++)
    {
        s->ch[k-len] = s->ch[k];
    }
    
    s->length -= len;
    return 1;
}

// 输出
void print(string s){
    int i;
    for(i=0; i<s.length;i++){
        printf("%c", s.ch[i]);
    }
    printf("\n");
}

void main(){
    string s1= initString();
    string s2= initString();
    string s3= initString();
    char ch[MAXSIZE];
    printf("请输入主串：\n");
    gets(ch);
    stringAssign(&s1,ch);
    printf("主串 s1 为：");
    print(s1);
    stringCopy(&s2,s1);
    printf("拷贝串操作结果如下，结果如下 s2 ：");
    print(s2);
    printf("删除操作（1——s1.length-3 全删）：");
    deleteString(&s2,1,s1.length-3);
    print(s2);
    printf("插入操作,插入到s2的第2个位置上，请输入插入的字符串：");
    gets(ch);
    stringAssign(&s3,ch);
    insertString(&s2,2,s3);
    print(s2);
    printf("取子串操作（取s1的子串【2-4】)：");
    substr(s1,2,3,&s3);
    print(s3);
    printf("串连接操作【将s1与s3合并】：");
    contact(&s1,s1,s2);
    print(s1);
}