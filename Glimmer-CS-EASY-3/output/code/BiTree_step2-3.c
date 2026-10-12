#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;                       // 节点存储的数据
    struct TreeNode *left;          // 左子树指针
    struct TreeNode *right;         // 右子树指针
} TreeNode;

//----------------------------------------------------------//

TreeNode* create_node(int value){

    TreeNode* new = (TreeNode*)malloc(sizeof(TreeNode));
    if (new == NULL) {
        printf("failed!\n");
        return NULL;
    }

    new->data = value;

    new->left = NULL;
    new->right = NULL;

    return new;
}


//---------------------------------------------------------
//三种遍历

//前序遍历
void preorder(TreeNode* root) {

    if (root == NULL) return;//遇到空节点终止
    
    printf("%d ", root->data);//1.访问根节点（打印自己）
    
    preorder(root->left);//2.递归左子树
    
    preorder(root->right);//3.递归右子树

}

//中序遍历
void inorder(TreeNode* root) {

    if (root == NULL) return;//遇到空节点终止
    
    inorder(root->left);//1.递归左子树
    
    printf("%d ", root->data);//2.访问根节点（打印自己）
    
    inorder(root->right);//3.递归右子树

}

//后序遍历
void postorder(TreeNode* root) {

    if (root == NULL) return;//遇到空节点终止
    
    postorder(root->left);//1.递归左子树
    
    postorder(root->right);//2.递归右子树
    
    printf("%d ", root->data);//3.访问根节点（打印自己）

}

//----------------------------栈操作----------------------------------//

typedef struct Stack {
    TreeNode **arr;//存放二叉树的指针
    int top;//栈顶指针
    int capacity;//栈的容量
} Stack;//定义栈的结构体
//创建栈
Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));//为栈结构体分配内存
    stack->arr = malloc(sizeof(TreeNode *) * capacity);//为栈的数组分配内存
    stack->top = -1;//初始化栈顶指针
    stack->capacity = capacity;//记录容量
    return stack;
}
int isEmpty(Stack *stack) {//判断栈是否为空
    return stack->top == -1;
}
//入栈操作
void push(Stack *stack, TreeNode *node) {

    if (stack->top == stack->capacity - 1) {
        return;
    }//若top达到上限,则不再入栈
    
    stack->arr[++stack->top] = node;//栈顶指针+1,将节点入栈
}
//出栈操作
TreeNode *pop(Stack *stack) {

    if (isEmpty(stack)) {
        return NULL;
    }//如果栈为空,则返回NULL

    return stack->arr[stack->top--];//栈顶指针-1,返回栈顶节点
}
//------------------------用栈操作实现前序遍历---------------------------//

void preorderTraversal(TreeNode *root) // 补全这个函数
{
    if (root == NULL) {
        return;
    }

    Stack *s = createStack(100);

    TreeNode *current = root;
    
    while (current != NULL || !isEmpty(s)) {

        while (current != NULL) {
            printf("%d ", current->data);
            push(s, current);
            current = current->left;
        }

        current = pop(s);
        current = current->right;
    }
    
    free(s->arr);
    free(s);

}//这块不太懂,ai生成后理解了一下

//----------------------------主函数----------------------------------//

int main(){
    
    TreeNode* root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);
    

    printf("前序遍历: ");
    preorder(root);
    printf("\n");

    printf("中序遍历: ");
    inorder(root);
    printf("\n");

    printf("后序遍历: ");
    postorder(root);
    printf("\n");
    //------------------------//

    printf("非递归前序遍历：");
    preorderTraversal(root);
    printf("\n");

    return 0;
}
