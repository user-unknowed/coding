#include <stdio.h>

/*
 * 基本递归计算斐波那契数列的第 n 项（从 1 开始计数）
 * 说明：fibo(1) = 1, fibo(2) = 1
 * 注意：此实现使用简单递归，时间复杂度为指数级，不适合计算很大的 n。
 */
int fibo(int n) {
    // 递归的基本情况：如果 n 为 1 或 2，返回 1（斐波那契数列的前两项）
    if (n == 1 || n == 2) {
        return 1;
    } else {
        // 递归调用：返回前两项之和：f(n) = f(n-1) + f(n-2)
        return fibo(n - 1) + fibo(n - 2);
    }
}

/*
 * 尾递归辅助函数，使用累加器模式优化斐波那契计算
 * current：当前项的值
 * next：下一项的值
 * n：剩余需要计算的步数
 */
int fibo_tail_helper(int current, int next, int n) {
    // 基本情况：当剩余步数为 1 时，返回当前项的值
    if (n == 1) {
        return current;
    }
    // 尾递归调用：更新当前项和下一项，并减少剩余步数
    return fibo_tail_helper(next, current + next, n - 1);
}

/*
 * 尾递归优化的斐波那契函数（从 1 开始计数）
 * 调用辅助函数并初始化参数
 */
int fibo_tail(int n) {
    // 处理特殊情况
    if (n <= 0) return 0;
    // 调用尾递归辅助函数，初始值设置为斐波那契数列的前两项
    return fibo_tail_helper(1, 1, n);
}

/*
 * 使用基本递归打印斐波那契数列
 */
void print_fibo_basic(int limit) {
    printf("使用基本递归计算斐波那契数列：\n");
    for (int i = 1; i <= limit; i++) {
        printf("%d ", fibo(i));
        if (i % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

/*
 * 使用尾递归打印斐波那契数列
 */
void print_fibo_tail(int limit) {
    printf("使用尾递归优化计算斐波那契数列：\n");
    for (int i = 1; i <= limit; i++) {
        printf("%d ", fibo_tail(i));
        if (i % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int main() {
    int choice;
    int n;
    
    printf("===== 斐波那契数列计算器 =====\n");
    printf("1. 计算单个斐波那契数\n");
    printf("2. 打印斐波那契数列前N项\n");
    printf("请选择操作 (1-2): ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("请输入要计算的项数 n: ");
            scanf("%d", &n);
            
            if (n <= 0) {
                printf("错误: 请输入正整数!\n");
                return 1;
            }
            
            // 对于较小的n值，可以使用基本递归；对于较大的n值，建议使用尾递归
            if (n <= 30) {
                printf("基本递归: fibo(%d) = %d\n", n, fibo(n));
            } else {
                printf("警告: 项数较大，推荐使用尾递归优化\n");
            }
            
            printf("尾递归优化: fibo(%d) = %d\n", n, fibo_tail(n));
            break;
            
        case 2:
            printf("请输入要打印的项数 (1-50): ");
            scanf("%d", &n);
            
            if (n <= 0 || n > 50) {
                printf("错误: 请输入1-50之间的整数!\n");
                return 1;
            }
            
            // 对于较小的n值，可以显示两种实现的结果进行比较
            if (n <= 20) {
                print_fibo_basic(n);
            } else {
                printf("警告: 项数较大，只显示尾递归优化结果\n");
            }
            
            print_fibo_tail(n);
            break;
            
        default:
            printf("无效选择!\n");
            return 1;
    }

    printf("\n提示: 尾递归版本比基本递归版本效率更高，特别是对于大数计算。\n");
    return 0;
}