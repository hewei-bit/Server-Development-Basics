/**
 * @File Name: rbtree_hw.c
 * @Brief :
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2022-03-13
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. 节点是红色或黑色。
// 2. 根节点是黑色。
// 3. 每个叶节点是黑色的。
// 4. 每个红色节点的两个子节点都是黑色。(从每个叶子到根的所有路径上不能有两个连续的红色节点)
// 5. 从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点。
#define RED 1
#define BLACK 2

typedef int KEY_TYPE;
//
typedef struct _rbtree_node
{
    unsigned char color;         //颜色
    struct _rbtree_node *right;  //右子树，比本身大
    struct _rbtree_node *left;   // 左子树，比本身小
    struct _rbtree_node *parent; // 父节点
    KEY_TYPE key;                // 节点本身的值
    void *value;
} rbtree_node;

typedef struct _rbtree
{
    rbtree_node *root; // 树头
    rbtree_node *nil;  // 所有叶子节点指向nil，通用的叶子节点
} rbtree;

// 找到最小
rbtree_node *rbtree_mini(rbtree *T, rbtree_node *x) {}
// 找到最大
rbtree_node *rbtree_maxi(rbtree *T, rbtree_node *x) {}
//
rbtree_node *rbtree_successor(rbtree *T, rbtree_node *x) {}
// 左旋
void rbtree_left_rotate(rbtree *T, rbtree_node *x) {}
// 右旋
void rbtree_right_rotate(rbtree *T, rbtree_node *y) {}
// 插入
void rbtree_insert_fixup(rbtree *T, rbtree_node *z) {}
void rbtree_insert(rbtree *T, rbtree_node *z) {}
// 删除
void rbtree_delete_fixup(rbtree *T, rbtree_node *x) {}
rbtree_node *rbtree_delete(rbtree *T, rbtree_node *z) {}
// 查找
rbtree_node *rbtree_search(rbtree *T, KEY_TYPE key) {}
// 用递归实现中序遍历
void rbtree_traversal(rbtree *T, rbtree_node *node) {}
int main()
{
    return 0;
}
// 父结点是祖父结点的左子树的情况
//     1. 叔结点是红色的
//     2. 叔结点是黑色的，而且当前结点是右孩子
//     3. 叔结点是黑色的，而且当前结点是左孩子

// 当前结点是父结点的左子树的情况
//     1. 当前结点的兄弟结点是红色的
//     2. 当前结点的兄弟结点是黑色的，而且兄弟结点的
//     两个孩子结点都是黑色的
//     3. 当前结点的兄弟结点是黑色的，而且兄弟结点的
//     左孩子是红色的，右孩子是黑色的
//     当前结点是父结点的左子树的情况
//     4. 当前结点的兄弟结点是黑色的，而且兄弟结点的
//     右孩子是红色的