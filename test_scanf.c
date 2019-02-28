// #include <stdio.h>
// int main(void)
// {
//     int i;
//     // i = 10;
//     scanf("%d", &i); //&i 表示变量 i 的地址，&是取地址符
//     printf("i = %d\n", i);
//     return 0;
// }

// 一次给多个变量赋值：
// # include <stdio.h>
// int main(void)
// {
//     int i, j;
//     scanf("%d%d", &i, &j);
//     printf("i = %d, j = %d\n", i, j);
//     return 0;
// }
// # include <stdio.h>
// int main(void)
// {
//     char i, j, k;
//     scanf("%c%c%c", &i, &j, &k);
//     printf("i = %c, j = %c, k = %c\n", i, j, k);
//     return 0;
// }
// 标准写法
// # include <stdio.h>
// int main(void)
// {
//     int i, j;
//     printf("请输入两个值，中间以空格分隔：");
//     scanf("%d%d", &i, &j);
//     printf("i = %d, j = %d\n", i, j);
//     return 0;
// }

// 如何输出 %d、\ 和双引号
# include <stdio.h>
int main(void)
{
    printf("%%d\n");
    printf("\\\n");
    printf("\"\"\n");
    return 0;
}