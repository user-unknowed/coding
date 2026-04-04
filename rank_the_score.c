//
// Created by ababa on 2026/3/30.
//
#include<stdio.h>

struct Score {
    int score;
}s[6];//结构体设置

void point_print(struct Score s[]) {
    for (int i = 0; i < 6; i++) {
        if (s[i].score > 90) {//注意数组s[i]表示方式
            printf("%d\n",s[i].score);
        }
    }
}

int main() {
    struct Score s[6];
    printf("give me 6 scores:\n");
    for (int i = 0; i < 6; i++) {
        scanf("%d", &s[i].score);
        printf("\n");
    }
    printf("the nicest scores are:\n");
    point_print(s);//注意数组s只写数组头
    return 0;
}