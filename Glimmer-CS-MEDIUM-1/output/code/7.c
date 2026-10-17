#include <stdio.h>
#include <stdbool.h>

// 定义简单队列结构用于 BFS
typedef struct {
    int pos;   // 当前节点编号 (0~15)
    int dist;  // 到达当前节点的最短步数
} Node;

int minStepsToCheese(int walls) {
    int start = 0;
    int target = 15;

    // 如果起点或终点本身是墙，直接不可达
    if ((walls & (1 << start)) || (walls & (1 << target))) {
        return -1;
    }

    // BFS 队列与访问位图
    Node queue[16];
    int front = 0, rear = 0;
    int visited = 0;

    // 起点入队并标记已访问 (请使用位运算)
    queue[rear++] = (Node){start, 0};
    visited |= (1 << start);

    // 上、下、左、右四个方向的节点偏移量
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    //请在TO DO 和END OF TO DO 行之间补全代码：
    //TO DO
    while (front < rear) {
        Node cur = queue[front++];

        if (cur.pos == target) {
            return cur.dist;
        }

        int r = cur.pos / 4;
        int c = cur.pos % 4;

        for(int i =0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) {
                continue;
            }

            int np = nr * 4 + nc;

            if ((walls & (1 << np)) || (visited & (1 << np))) {
                continue;
            }
            visited |= (1 << np);
            queue[rear++] = (Node){np, cur.dist + 1};
        }
    }
    //END OF TO DO

    return -1; // 无法到达
}

int main() {
    int walls = (1 << 5) | (1 << 10); // 5号和10号格子是墙
    int steps = minStepsToCheese(walls);
    printf("Minimum steps: %d\n", steps); // 应输出 6
    return 0;
}