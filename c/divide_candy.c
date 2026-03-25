//
// Created by ababa on 2026/1/25.
//
#include<stdio.h>
int function(int n) {
    int count = 0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(i<=n) {
                count++;
            }
        }
    }
    //DFS算法，即"一条路走到黑，走到黑就回头"
    return count;
}
int main() {
    int n,count=0;
    scanf("%d",&n);
    count = function(n);
    printf("%d",count);
    return 0;
}
