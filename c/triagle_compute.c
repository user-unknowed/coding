#include<stdio.h>
#include<math.h>
int main() {
    int input;
    double in,out;
    double (*p)(double);
    printf("print the number you will count:\n");
    scanf("%lf",&in);
    printf("print the way you would like to calculate:\n");
    printf("1.sin\n 2.cos\n 3.tan\n ");
    scanf("%d",&input);
    if (input==1) {
        p=sin;
    } else if (input==2) {
        p=cos;
    } else if (input==3) {
        p=tan;
    } else {
        printf("error");
        return 1;
    }
    out=(*p)(in);//调用函数指针p指向的函数，计算in的三角函数值
    printf("the result is %f",out);
    return 0;

}
