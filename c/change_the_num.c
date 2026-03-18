//
// Created by ababa on 2026/3/18.
//
#include <stdio.h>
void change(float *x,int k) {
    for (int i=0;i<k;i++) {
        *(x+i)=0;
    }
}
void print(float *x,int n) {
    for (int i=0;i<n;i++) {
        printf("%f",*(x+i));
    }
}
int main() {
    float a[10];
    float *p=&a;
    int k;
    printf("10 float:\n");
    for (int i = 0; i < 10; i++) {
        scanf("%f", &a[i]);
    }
    printf("enter the number:\n");
    scanf("%d",&k);
    change(p,k);
    print(p,10);
    return 0;
}