#include <stdio.h>

/* 冒泡排序：把数组 arr 的前 n 个元素按从小到大排序 */
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0; // 本轮是否发生过交换的标志（用于提前退出优化）
        /* 每轮把当前未排序部分最大的元素“冒泡”到末尾 */
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        /* 若本轮没有任何交换，数组已排序，直接结束 */
        if (!swapped) break;
    }
}

int main(void) {
    int n;
    /* 读取元素个数（正整数） */
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("请输入正整数个数\n");
        return 1;
    }

    int arr[n];
    /* 读取 n 个正整数（假设输入皆为正数） */
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    /* 排序 */
    bubble_sort(arr, n);

    /* 输出排序结果（空格分隔） */
    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;
}