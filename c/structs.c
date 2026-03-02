//
// Created by ababa on 2026/3/2.
//


#include<stdio.h>
struct Date{
    int year;
    int month;
    int day;
};//分号不能省
struct Num {
    int a;
    char b[4];
    struct Date aa;//可以嵌套调用
};
int main() {
    struct Date aa={2026,3,2};
    struct Num num={100,"what",aa};
    printf("%d,%s\nin%d/%d/%d",num.a,num.b,num.aa.year,num.aa.month,num.aa.day);
    //输出方法（其实是直接输出，就是多了一些.（组合运算符）来"引出"变量
    return 0;
}