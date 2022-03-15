/**
 * @File Name: rbtree_hw.c
 * @Brief : 红黑树实现
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
//红黑树节点
typedef struct _rbtree_node
{
    unsigned char color;         //颜色
    struct _rbtree_node *right;  //右子树，比本身大
    struct _rbtree_node *left;   // 左子树，比本身小
    struct _rbtree_node *parent; // 父节点
    KEY_TYPE key;                // 节点本身的值
    void *value;                 // 该节点挂载的值
} rbtree_node;

typedef struct _rbtree
{
    rbtree_node *root; // 树头
    rbtree_node *nil;  // 所有叶子节点指向nil，通用的叶子节点
} rbtree;

// 找到最小
rbtree_node *rbtree_mini(rbtree *T, rbtree_node *x)
{
    while (x->left != T->nil)
    {
        x = x->left;
    }
    return x;
}

// 找到最大
rbtree_node *rbtree_maxi(rbtree *T, rbtree_node *x)
{
    while (x->right != T->nil)
    {
        x = x->right;
    }
    return x;
}

//找到最接近的左子树
rbtree_node *rbtree_successor(rbtree *T, rbtree_node *x)
{
    rbtree_node *y = x->parent;
    // 如果x不是叶子节点，则返回的x右子树的最小值
    if (x->right != T->nil)
    {
        return rbtree_mini(T, x->right);
    }

    while ((y != T->nil) && (x == y->right))
    {
        x = y;
        y = y->parent;
    }
    return y;
}

// 左旋
void rbtree_left_rotate(rbtree *T, rbtree_node *x)
{
    // x  --> y  ,  y --> x,   right --> left,  left --> right
    rbtree_node *y = x->right;

    x->right = y->left;
    // y的左子树不是叶子节点
    if (y->left != T->nil)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;
    // 确定 y 是根节点还是左子树还是右子树
    if (x->parent == T->nil)
    {
        T->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    // 重新连接x和y
    y->left = x;
    x->parent = y;
}

// 右旋（把左旋中的x和y互换即可）
void rbtree_right_rotate(rbtree *T, rbtree_node *y)
{
    rbtree_node *x = y->left;

    y->left = x->right;
    if (x->right != T->nil)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == T->nil)
    {
        T->root = x;
    }
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }
    else
    {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

// 插入补充
// 父结点是祖父结点的左子树的情况
//     1. 叔结点是红色的
//     2. 叔结点是黑色的，而且当前结点是右孩子
//     3. 叔结点是黑色的，而且当前结点是左孩子
void rbtree_insert_fixup(rbtree *T, rbtree_node *z)
{
    while (z->parent->color == RED)
    {
        // z ---> RED
        if (z->parent == z->parent->parent->left)
        {
            rbtree_node *y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rbtree_left_rotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_right_rotate(T, z->parent->parent);
            }
        }
        else
        {
            rbtree_node *y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; // z --> RED
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rbtree_right_rotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_left_rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

// 插入
void rbtree_insert(rbtree *T, rbtree_node *z)
{
    rbtree_node *y = T->nil;
    rbtree_node *x = T->root;

    // 找到插入的地方
    while (x != T->nil)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else if (z->key > x->key)
        {
            x = x->right;
        }
        else
        {
            // 已经存在
            return;
        }
    }

    // 确定z是y的左子树还是右子树
    z->parent = y;
    if (y == T->nil)
    {
        T->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    // 先当作叶子节点
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;

    // 开始调整
    rbtree_insert_fixup(T, z);
}

// 删除补充
// 当前结点是父结点的左子树的情况
//     1. 当前结点的兄弟结点是红色的
//     2. 当前结点的兄弟结点是黑色的，而且兄弟结点的
//     两个孩子结点都是黑色的
//     3. 当前结点的兄弟结点是黑色的，而且兄弟结点的
//     左孩子是红色的，右孩子是黑色的
//     当前结点是父结点的左子树的情况
//     4. 当前结点的兄弟结点是黑色的，而且兄弟结点的
//     右孩子是红色的
void rbtree_delete_fixup(rbtree *T, rbtree_node *x)
{
    while ((x != T->root) && (x->color == BLACK))
    {
        if (x == x->parent->left)
        {
            rbtree_node *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;

                rbtree_left_rotate(T, x->parent);
                w = x->parent->right;
            }

            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbtree_right_rotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rbtree_left_rotate(T, x->parent);

                x = T->root;
            }
        }
        else
        {
            rbtree_node *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rbtree_right_rotate(T, x->parent);
                w = x->parent->left;
            }

            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {

                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbtree_left_rotate(T, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rbtree_right_rotate(T, x->parent);

                x = T->root;
            }
        }
    }

    x->color = BLACK;
}

rbtree_node *rbtree_delete(rbtree *T, rbtree_node *z)
{
    rbtree_node *y = T->nil;
    rbtree_node *x = T->nil;
    // 先找替换用的节点y
    // 1.没有左右子树
    // 2.有左子树或右子树
    if ((z->left == T->nil) || (z->right == T->nil))
    {
        y = z;
    }
    // 3.有左子树且有右子树
    else
    {
        y = rbtree_successor(T, z);
    }

    //补充y被换走以后的位置
    if (y->left != T->nil)
    {
        x = y->left;
    }
    else if (y->right != T->nil)
    {
        x = y->right;
    }

    // 在把y换走之前先把坑补上
    x->parent = y->parent;
    if (y->parent == T->nil)
    {
        T->root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    // 把y换到z的位置上
    if (y != z)
    {
        z->key = y->key;
        z->value = y->value;
    }

    if (y->color == BLACK)
    {
        rbtree_delete_fixup(T, x);
    }

    return y;
}

// 查找
rbtree_node *rbtree_search(rbtree *T, KEY_TYPE key)
{
    rbtree_node *node = T->root;
    while (node != T->nil)
    {
        if (key < node->key)
        {
            node = node->left;
        }
        else if (key > node->key)
        {
            node = node->right;
        }
        else
        {
            return node;
        }
    }
    return T->nil;
}

// 用递归实现中序遍历
void rbtree_traversal(rbtree *T, rbtree_node *node)
{
    if (node != T->nil)
    {
        rbtree_traversal(T, node->left);
        printf("key:%d, color:%d\n", node->key, node->color);
        rbtree_traversal(T, node->right);
    }
}

int main()
{
    int keyArray[20] = {24, 25, 13, 35, 23, 26, 67, 47, 38, 98, 20, 19, 17, 49, 12, 21, 9, 18, 14, 15};

    rbtree *T = (rbtree *)malloc(sizeof(rbtree));
    if (T == NULL)
    {
        printf("malloc failed\n");
        return -1;
    }

    T->nil = (rbtree_node *)malloc(sizeof(rbtree_node));
    T->nil->color = BLACK;
    T->root = T->nil;

    rbtree_node *node = T->nil;
    int i = 0;
    for (i = 0; i < 20; i++)
    {
        node = (rbtree_node *)malloc(sizeof(rbtree_node));
        node->key = keyArray[i];
        node->value = NULL;

        rbtree_insert(T, node);
    }

    rbtree_traversal(T, T->root);
    printf("----------------------------------------\n");

    for (i = 0; i < 20; i++)
    {
        rbtree_node *node = rbtree_search(T, keyArray[i]);
        rbtree_node *cur = rbtree_delete(T, node);

        free(cur);

        rbtree_traversal(T, T->root);
        printf("----------------------------------------\n");
    }

    return 0;
}
