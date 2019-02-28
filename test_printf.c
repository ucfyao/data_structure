// 如何输出 %d、\ 和双引号
# include <stdio.h>
typedef struct
{
    int *elem; // 存储空间地址
    int length; //当前长度
    int listsize; // 当前分配的存储容量
} SqList;

#define list_init_size 80 //初始分配存储空间
#define listincreament 10 //存储空间分配增量
#define OVERFLOW -2

int main(void)
{
    // printf("%%d\n");
    // printf("\\\n");
    // printf("\"\"\n");
    // return 0;
    SqList L;
     //动态开辟一维数组
    L.elem = (int *) malloc( list_init_size * sizeof(int) );
    //存储分配失败
    if(!L.elem)
        exit(OVERFLOW);
    //空表长度初始化为0；
    L.length = 0;
    //存储的初始容量为初始分配空间
    L.listsize = list_init_size;
    printf("elem=%p,elem=%d,length=%d,listsize=%d\n", L.elem ,L.elem , L.length ,L.listsize );

}
// 默认都是二进制存储的，用输出控制符确定显示为什样子的。
// 输出控制符。
// %d	按十进制整型数据的实际长度输出。
// %ld	输出长整型数据。
// %md	m 为指定的输出字段的宽度。如果数据的位数小于 m，则左端补以空格，若大于 m，则按实际位数输出。
// %u	输出无符号整型（unsigned）。输出无符号整型时也可以用 %d，这时是将无符号转换成有符号数，然后输出。但编程的时候最好不要这么写，因为这样要进行一次转换，使 CPU 多做一次无用功。
// %c	用来输出一个字符。
// %f	用来输出实数，包括单精度和双精度，以小数形式输出。不指定字段宽度，由系统自动指定，整数部分全部输出，小数部分输出 6 位，超过 6 位的四舍五入。
// %.mf	输出实数时小数点后保留 m 位，注意 m 前面有个点。
// %o	以八进制整数形式输出，这个就用得很少了，了解一下就行了。
// %s	用来输出字符串。用 %s 输出字符串同前面直接输出字符串是一样的。但是此时要先定义字符数组或字符指针存储或指向字符串，这个稍后再讲。
// %x（或 %X 或 %#x 或 %#X）	以十六进制形式输出整数，这个很重要。

