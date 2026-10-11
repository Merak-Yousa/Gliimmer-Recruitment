//使用顺序表完成二叉树操作
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TREE_SIZE 100
/*
 * 顺序存储二叉树结点
 * - data：结点数据
 * - used：当前位置是否有结点
 */
typedef struct {
    int data;
    bool used;
} SeqTreeNode;

/*
 * 顺序存储二叉树
 * - nodes：结点数组
 * - size：数组最大容量
 */
typedef struct {
    SeqTreeNode nodes[MAX_TREE_SIZE];
    int size;
} SeqBiTree;
/*
 * 初始化顺序存储二叉树
 * - tree：指向顺序存储二叉树的指针
 */

//-------------------------------------
//1.初始化二叉树
void init_tree(SeqBiTree *tree){
    for(int i = 0; i < MAX_TREE_SIZE; i++){
        tree->nodes[i].used = false;
    }//从1到MAX_TREE_SIZE-1,used全部标记为空
    tree->size = 0;//树的节点数量为0
}

//2.创建根节点
bool set_root(SeqBiTree *tree, int value){
    if(tree->nodes[1].used){
        return false;
    }//判断根节点是否被占用
tree->nodes[1].data = value;//填入数据
    tree->nodes[1].used = true;//标记为已使用
    tree->size++;//节点数量+1
    return true;
}

//3.创建左孩子
bool set_left_child(SeqBiTree *tree, int parent_node, int value) {
    int lchild_index = 2 * parent_node; //左孩子下标
    //防御性检查
    if (lchild_index >= MAX_TREE_SIZE || tree->nodes[lchild_index].used || !tree->nodes[parent_node].used) {
        return false; //下标越界或该位置被占用或父节点不存在
    }

    tree->nodes[lchild_index].data = value; //填入数据
    tree->nodes[lchild_index].used = true; //标记为已使用
    tree->size++; //节点数量+1
    return true;
}

///4.创建右孩子
bool set_right_child(SeqBiTree *tree, int parent_node, int value) {
    int rchild_index = 2 * parent_node + 1; //右孩子下标
    //防御性检查
    if (rchild_index >= MAX_TREE_SIZE || tree->nodes[rchild_index].used || !tree->nodes[parent_node].used) {
        return false; 
    }

    tree->nodes[rchild_index].data = value;
    tree->nodes[rchild_index].used = true;
    tree->size++;
    return true;//同创建左孩子
}

//5.层序遍历
void level_order(SeqBiTree *tree){
    if (tree->size == 0) {
        printf("The tree is empty.\n");
        return;
    }//树为空,结束

    printf("result:\n");

    int limit = 1;//第一层结束的下标
    
    for (int i = 1; i < MAX_TREE_SIZE; i++) {

        if (tree->nodes[i].used) {
            printf("%d ", tree->nodes[i].data);//有节点则打印数据
        } else {
            printf("-1 ");//空节点用-1表示
        }

        if (i == limit) {
            printf("\n");
            limit = limit * 2 + 1; //当到达当前层的最后下标时,更新下一层的最后下标并换行
        }

        if (i >= MAX_TREE_SIZE) {
            break; //如果打印完最后一层,则退出循环
        }
    }

}

//6.主函数测试
int main() {

    SeqBiTree tree;
    init_tree(&tree);//创建和初始化

    set_root(&tree, 1);//创建根节点
    set_left_child(&tree, 1, 2);//创建左孩子
    set_right_child(&tree, 1, 3);//创建右孩子
    set_left_child(&tree, 2, 4);
    set_right_child(&tree, 2, 5);
    set_left_child(&tree, 3, 6);
    set_right_child(&tree, 3, 7);

    level_order(&tree);//层序遍历

    return 0;
}
//测试完毕