//
// Created by ababa on 2026/3/17.
//
/*题目：
 * 使用指针编程实现：输入3个正整数，按由小到大顺序输出。
 */
#include <stdio.h>
#include <stdlib.h>
void swap(int *x,int *y) {
    int *tmp=NULL;//用malloc分配内存给*tmp
    if (*x>*y) {
        *tmp=*x;
        *x=*y;
        *y=*tmp;
    }
    free(tmp);//释放原tmp占用内存
}
void input(int *p1,int *p2,int *p3) {
    swap(*p1,*p2);
    swap(*p1,*p3);
    swap(*p2,*p3);
}
int main() {
    int a,b,c;
    int *pa=&a;
    int *pb=&b;
    int *pc=&c;
    printf("enter 3 number:\n");
    scanf("%d %d %d",&a,&b,&c);
    input(*pa,*pb,*pc);
    printf("out:%d %d %d",*pa,*pb,*pc);
    return 0;
}