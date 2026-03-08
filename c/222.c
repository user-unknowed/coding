#include <stdio.h>
#include <string.h>

// 定义结构体Student,学生姓名不超过10个字符
// 三门课程成绩均为百分制，只取整数；平均分带小数
struct Student {
    char name[10];
    int score1;  // 更清晰的变量名
    int score2;
    int score3;
    float average;  // 修正拼写
};

// 函数原型声明
void input(struct Student s[], int n);
void average(struct Student s[], int n);
void print(struct Student s[], int n);

int main() {
    // 定义结构体数组stud[3]
    struct Student stud[3];
    
    // 调用input()、average()、print()三个函数
    input(stud, 3);
    average(stud, 3);
    print(stud, 3);
    
    return 0;
}

// 定义输入n名学生的姓名、三门课程成绩的函数
void input(struct Student s[], int n) {
    for (int i = 0; i < n; i++) {  // 使用参数n
        printf("请输入第%d名学生数据：\n", i + 1);
        printf("name: ");
        scanf("%9s", s[i].name);  // 限制输入长度，防止缓冲区溢出
        printf("score1: ");
        scanf("%d", &s[i].score1);
        printf("score2: ");
        scanf("%d", &s[i].score2);
        printf("score3: ");
        scanf("%d", &s[i].score3);
        
        // 输入验证
        if (s[i].score1 < 0 || s[i].score1 > 100 ||
            s[i].score2 < 0 || s[i].score2 > 100 ||
            s[i].score3 < 0 || s[i].score3 > 100) {
            printf("警告：成绩应在0-100之间！\n");
        }
    }
    printf("\n");
}

// 定义计算n名学生三门课程平均分的函数
void average(struct Student s[], int n) {
    for (int i = 0; i < n; i++) {  // 使用参数n
        s[i].average = (s[i].score1 + s[i].score2 + s[i].score3) / 3.0;
    }
}

// 定义输出n名学生的姓名、三门课程成绩、平均分的函数
void print(struct Student s[], int n) {
    printf("学生成绩列表：\n");
    for (int i = 0; i < n; i++) {  // 使用参数n
        printf("name:%s, score1:%d, score2:%d, score3:%d, average:%.2f\n",
               s[i].name, s[i].score1, s[i].score2, s[i].score3, s[i].average);
    }
    printf("\n");
}