//
// Created by ababa on 2026/3/31.
//
#include <stdio.h>
void find(int * a, int n,int * p_max,int * p_min) {
    *p_max = a[0];
    *p_min = a[0];
    for (int i=1; i<n ;i++) {
        if(a[i] > *p_max) {
        *p_max = a[i];
        }if(a[i] < *p_min) {
        *p_min = a[i];
        }
    }return *p_max,*p_min;
}
int main() {
    int a[10];
    int * p_max,*p_min;
    printf("10 numbers:\n");
    for(int i = 0;i < 10;i++) {
        scanf("%d",&a[i]);
    }
    find(a,10,&p_max,&p_min);
    printf("%d",*p_max);
    printf("%d",*p_min);
    return 0;
}