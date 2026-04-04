//
// Created by ababa on 2026/2/4.
//
#include<stdio.h>
int function(int n,int m){
    int a[3]={1,2,3};
    if(n-a[2]>=0){
        m++;
        n=n-a[2];
        return function(n,m);
    }
    else{
        if(n-a[1]>=0){
            n=n-a[1];
            m++;
            return function(n,m);
        }
        else{
            if(n-a[0]>=0){
                n=n-a[0];
                m++;
                return function(n,m);
            }
            else{
                return m;
            }
        }
    }
}
int main(){
    int sum,n;
    scanf("%d",&n);
    sum=function(n,0);
    printf("%d",sum);
    return 0;
}