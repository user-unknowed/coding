// 包含标准输入输出头文件，用于控制台输入输出
#include <stdio.h>
// 包含布尔类型头文件，用于使用bool类型
#include <stdbool.h>

// 定义迷宫的最大行数
#define MAX_R 20
// 定义迷宫的最大列数
#define MAX_C 20

// 点结构定义，用于表示迷宫中的坐标
typedef struct {
    int r; // 行坐标
    int c; // 列坐标
} Point;

// 队列结构定义，用于BFS算法
typedef struct {
    Point data[MAX_R * MAX_C]; // 存储队列元素的数组
    int front; // 队首指针
    int rear;  // 队尾指针
} Queue;

/**
 * 初始化队列
 * @param q 队列指针
 */
void initQueue(Queue *q) {
    q->front = q->rear = 0; // 将队首和队尾指针都初始化为0
}

/**
 * 检查队列是否为空
 * @param q 队列指针
 * @return 如果队列为空返回true，否则返回false
 */
bool isEmpty(Queue *q) {
    return q->front == q->rear; // 队首和队尾指针相等表示队列为空
}

/**
 * 入队操作
 * @param q 队列指针
 * @param r 行坐标
 * @param c 列坐标
 */
void enqueue(Queue *q, int r, int c) {
    q->data[q->rear].r = r; // 将行坐标存入队尾
    q->data[q->rear].c = c; // 将列坐标存入队尾
    q->rear++; // 队尾指针后移
}

/**
 * 出队操作
 * @param q 队列指针
 * @return 队首元素（坐标点）
 */
Point dequeue(Queue *q) {
    return q->data[q->front++]; // 返回队首元素并将队首指针后移
}

/**
 * 主函数，程序的入口点
 * @return 0 表示程序正常结束
 */
int main() {
    int R, C; // 迷宫的行数和列数
    char maze[MAX_R][MAX_C + 1]; // 存储迷宫数据，+1用于存储字符串结束符'\0'
    bool visited[MAX_R][MAX_C] = {false}; // 标记数组，记录每个位置是否已访问
    Queue q; // BFS使用的队列
    
    // 读取输入的迷宫行数和列数
    scanf("%d %d", &R, &C);
    // 读取迷宫的每一行数据
    for (int i = 0; i < R; i++) {
        scanf("%s", maze[i]);
    }
    
    // 初始化队列
    initQueue(&q);
    
    // 检查起点是否为通路，如果是则入队并标记为已访问
    if (maze[0][0] == '.') {
        enqueue(&q, 0, 0); // 起点(0,0)入队
        visited[0][0] = true; // 标记起点为已访问
    }
    
    // 方向数组：上、下、左、右
    int dr[4] = {-1, 1, 0, 0}; // 行的变化量：上移-1，下移+1，左右移0
    int dc[4] = {0, 0, -1, 1}; // 列的变化量：上下移0，左移-1，右移+1
    
    // BFS搜索主循环，当队列不为空时继续执行
    while (!isEmpty(&q)) {
        Point cur = dequeue(&q); // 取出队首元素
        
        // 检查当前位置是否为终点（右下角）
        if (cur.r == R - 1 && cur.c == C - 1) {
            printf("1\n"); // 如果到达终点，输出1表示可达
            return 0; // 结束程序
        }
        
        // 遍历四个方向（上、下、左、右）
        for (int i = 0; i < 4; i++) {
            // 计算新位置的行坐标
            int nr = cur.r + dr[i];
            // 计算新位置的列坐标
            int nc = cur.c + dc[i];
            
            // 检查新坐标是否合法（在迷宫内）、是否为通路（.）且未访问
            if (nr >= 0 && nr < R && nc >= 0 && nc < C &&
                maze[nr][nc] == '.' && !visited[nr][nc]) {
                visited[nr][nc] = true; // 标记新位置为已访问
                enqueue(&q, nr, nc); // 将新位置入队
            }
        }
    }
    
    // BFS结束后仍未到达终点，说明从起点到终点不可达
    printf("-1\n");
    // 结束程序
    return 0;
}