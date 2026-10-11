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

//------------------------------------------------------------//
int main(){
    
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    
    return 0;
}
