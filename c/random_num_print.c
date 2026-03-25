//
// Created by ababa on 2026/3/24.
//
#include <stdio.h>
#include <stdlib.h>//如要生成随机数，必须包含这个头文件
#include <time.h>
int main()
{
    int a[4][5]={0};
    void change_values(int *p, int n);
    void print_array(int (*p)[5],int m);

    printf("修改前，二维数组各行各列元素：\n");
    print_array(a,4);
    change_values((int*)a,20);//调用change_values函数修改数组元素的值
    printf("修改后，二维数组各行各列元素：\n");
    print_array(a,4);
    return 0;
}

//函数change_values功能：生成1-100之间的随机整数修改数组各元素的值
//形参：p是数组的首地址，n是数组元素个数
void change_values(int *p, int n)
{
    srand(time(0));//设置种子，避免每次运行程序时都得到相同的随机序列
    for(int i=0;i<n;i++){
        *(p+i)=rand()%100+1;//生成随机数,并赋值给指针
    }
    printf("\n");
    //代码段1
}

//函数print_array功能：输出二维数组各行各列元素的值
//形参：p是数组的首行地址，m是数组的行数(列数为5,以下不再重复)
void print_array(int (*p)[5],int m)
{
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<5;j++){
            printf("%d",*(*(p+i)+j));
        }
    }
    //代码段2
    printf("\n");
}